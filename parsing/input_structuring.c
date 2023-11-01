/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_structuring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:03:26 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/01 08:38:20 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	types_separation(t_list *prime, t_comp **cmpa)
{
	char	*tmp;
	bool	c;

	c = false;
	while (prime)
	{
		tmp = (char *)(prime->content);
		if (*tmp == '\'' || *tmp == '\"')
			c = types_separation_quotes(cmpa, tmp);
		else if (*tmp == ' ' || *tmp == '|')
			c = types_separation_pipe_space(cmpa, tmp, prime);
		else if ((*tmp == '<' && *(tmp + 1) == '<')
			|| (*tmp == '>' && *(tmp + 1) == '>'))
			c = types_separation_redir_1(cmpa, tmp, prime);
		else if (*tmp == '<' || *tmp == '>')
			c = types_separation_redir_2(cmpa, tmp, prime);
		else if (!ft_strchr(" |<>\0", *tmp))
			c = types_separation_word(cmpa, tmp, prime);
		if (c)
			prime = prime->next;
	}
}

bool	types_separation_word(t_comp **cmpa, char *tmp, t_list *prime)
{
	int		i;
	void	*t;
	char	*w;

	i = 0;
	while (!ft_strchr(" |<>\0", tmp[i]))
		i++;
	t = (void *)ft_substr(tmp, i, INT_MAX);
	w = ft_substr(tmp, 0, i);
	if (ft_strchr(w, '$'))
		ft_comp_add_back(cmpa, ft_compnew(w, word, true));
	else
		ft_comp_add_back(cmpa, ft_compnew(w, word, false));
	free(prime->content);
	prime->content = t;
	if (!*(char *)(prime->content))
		return (true);
	return (false);
}

bool	types_separation_redir_1(t_comp **cmpa, char *tmp, t_list *prime)
{
	void	*t;

	if (*tmp == '<')
	{
		t = (void *)ft_substr(tmp, 2, INT_MAX);
		free(prime->content);
		prime->content = t;
		ft_comp_add_back(cmpa, ft_compnew("<<", here_doc, false));
		if (!*(char *)(prime->content))
			return (true);
	}
	else
	{
		t = (void *)ft_substr(tmp, 2, INT_MAX);
		free(prime->content);
		prime->content = t;
		ft_comp_add_back(cmpa, ft_compnew(">>", app_op, false));
		if (!*(char *)(prime->content))
			return (true);
	}
	return (false);
}

bool	types_separation_redir_2(t_comp **cmpa, char *tmp, t_list *prime)
{
	void	*t;

	if (*tmp == '<')
	{
		t = (void *)ft_substr(tmp, 1, INT_MAX);
		free(prime->content);
		prime->content = t;
		ft_comp_add_back(cmpa, ft_compnew("<", r_inp, false));
		if (!*(char *)(prime->content))
			return (true);
	}
	else
	{
		t = (void *)ft_substr(tmp, 1, INT_MAX);
		free(prime->content);
		prime->content = t;
		ft_comp_add_back(cmpa, ft_compnew(">", r_out, false));
		if (!*(char *)(prime->content))
			return (true);
	}
	return (false);
}

bool	types_separation_quotes(t_comp **cmpa, char *tmp)
{
	if (*tmp == '\'')
		ft_comp_add_back(cmpa, ft_compnew(ft_strdup(tmp), s_quote, false));
	else if ((*tmp == '\"') && ft_strchr(tmp, '$'))
		ft_comp_add_back(cmpa, ft_compnew(ft_strdup(tmp), d_quote, true));
	else if ((*tmp == '\"') && !ft_strchr(tmp, '$'))
		ft_comp_add_back(cmpa, ft_compnew(ft_strdup(tmp), d_quote, false));
	return (true);
}
