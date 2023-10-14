/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:48:59 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/14 07:03:35 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_files(t_comp *cmpa)
{
	while (cmpa)
	{
		if (cmpa->tok == redir_input || cmpa->tok == redir_output
			|| cmpa->tok == here_doc || cmpa->tok == append_operator)
		{
			if (check_next(cmpa))
				cmpa = cmpa->next;
			else if (cmpa->next && cmpa->next->next
				&& cmpa->next->tok == space && check_next(cmpa->next))
				cmpa = cmpa->next;
			else
				return (false); 
		}
		else
			cmpa = cmpa->next;
	}
	return (true);
}

bool	check_next(t_comp *cmpa)
{
	if (cmpa->next && (cmpa->next->tok == d_quote
			|| cmpa->next->tok == s_quote
			|| cmpa->next->tok == word || cmpa->next->tok == delimiter))
		return (true);
	return (false);
}

void	here_doc_processes(t_comp *cmpa)
{
	bool	c;

	while (cmpa)
	{
		c = false;
		if (cmpa->tok == here_doc)
		{
			if (cmpa->next)
				cmpa = cmpa->next;
			if (cmpa->next && (cmpa->tok == space))
				cmpa = cmpa->next;
			if (cmpa->tok == word)
				cmpa->expanded = true;
			cmpa->tok = delimiter;
			while (cmpa->next && check_next(cmpa))
			{
				if (!c && (cmpa->tok == d_quote || cmpa->tok == s_quote
						|| cmpa->next->tok == d_quote
						|| cmpa->next->tok == s_quote))
					c = true;
				cmpa->data = join_quotes(cmpa->data, cmpa->next->data);
				ft_comp_n_del(&cmpa, cmpa->next, c);
			}
		}
		else
			cmpa = cmpa->next;
	}
}

char	*join_quotes(char *first, char *last)
{
	char	*t_first;
	char	*t_last;
	char	*ret;

	t_first = NULL;
	t_last = NULL;
	if (*first == '\'')
		t_first = ft_strtrim(first, "\'");
	else if (*first == '\"')
		t_first = ft_strtrim(first, "\"");
	else
		t_first = ft_strdup(first);
	if (*last == '\'')
		t_last = ft_strtrim(last, "\'");
	else if (*last == '\"')
		t_last = ft_strtrim(last, "\"");
	else
		t_last = ft_strdup(last);
	ret = ft_strjoin(t_first, t_last);
	if (t_first)
		free(t_first);
	if (t_last)
		free(t_last);
	return (free(first), free(last), ret);
}

void	ft_comp_n_del(t_comp **cmpa, t_comp *next, bool c)
{
	t_comp	*tmp;

	if (c)
		(*cmpa)->expanded = false;
	tmp = next->next;
	free(next);
	(*cmpa)->next = tmp;
}
