/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_processes_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:55:25 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/17 08:24:44 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trim_quotes(t_comp *cmpa)
{
	char	*tmp;
	t_comp	*ctmp;
	t_comp	*ctm;

	ctmp = cmpa;
	ctm = cmpa;
	while (cmpa)
	{
		if (cmpa->tok == d_quote || cmpa->tok == s_quote)
		{
			if (*(cmpa->data) == '\'')
				tmp = ft_strtrim(cmpa->data, "\'");
			else
				tmp = ft_strtrim(cmpa->data, "\"");
			free(cmpa->data);
			cmpa->data = tmp;
			cmpa->tok = word;
		}
		cmpa = cmpa->next;
	}
	join_words(ctmp);
	delete_spaces(ctm);
}

void	join_words(t_comp *cmpa)
{
	while (cmpa)
	{
		if (cmpa->tok == word && check_next(cmpa))
		{
			while (check_next(cmpa))
			{
				cmpa->data = join_quotes(cmpa, cmpa->next);
				ft_comp_nd_del(&cmpa, cmpa->next);
			}
		}
		else
			cmpa = cmpa->next;
	}
}

void	ft_comp_nd_del(t_comp **cmpa, t_comp *next)
{
	t_comp	*tmp;

	tmp = next->next;
	free(next);
	(*cmpa)->next = tmp;
}

void	delete_spaces(t_comp *cmpa)
{
	while (cmpa)
	{
		if (cmpa->next && cmpa->next->tok == space)
			ft_comp_nd_del(&cmpa, cmpa->next);
		else
			cmpa = cmpa->next;
	}
}

char	*join_quotes(t_comp *cmpa, t_comp *next)
{
	char	*t_first;
	char	*t_last;
	char	*ret;

	t_first = NULL;
	t_last = NULL;
	if (*(cmpa->data) == '\'' && cmpa->tok != word && cmpa->tok != delimiter)
		t_first = ft_strtrim(cmpa->data, "\'");
	else if (*(cmpa->data) == '\"' && cmpa->tok != word
		&& cmpa->tok != delimiter)
		t_first = ft_strtrim(cmpa->data, "\"");
	else
		t_first = ft_strdup(cmpa->data);
	if (*(next->data) == '\'' && next->tok != word)
		t_last = ft_strtrim(next->data, "\'");
	else if (*(next->data) == '\"' && next->tok != word)
		t_last = ft_strtrim(next->data, "\"");
	else
		t_last = ft_strdup(next->data);
	ret = ft_strjoin(t_first, t_last);
	if (t_first)
		free(t_first);
	if (t_last)
		free(t_last);
	return (free(cmpa->data), free(next->data), ret);
}
