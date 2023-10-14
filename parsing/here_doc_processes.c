/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:48:59 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/14 11:59:57 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			here_doc_processes_assistant(&cmpa, &c);
			cmpa = cmpa->next;
	}
}

void	here_doc_processes_assistant(t_comp **cmpa, bool	*c)
{
	if ((*cmpa)->next && (*cmpa)->next->tok == here_doc)
		return ;
	if ((*cmpa)->next)
		(*cmpa) = (*cmpa)->next;
	if ((*cmpa)->next && ((*cmpa)->tok == space))
		(*cmpa) = (*cmpa)->next;
	if ((*cmpa)->tok == word)
		(*cmpa)->expanded = true;
	if ((*cmpa)->tok != pipe_op && (*cmpa)->tok != redir_input && (*cmpa)->tok != redir_output
		&& (*cmpa)->tok != append_operator && (*cmpa)->tok != here_doc)
		(*cmpa)->tok = delimiter;
	while ((*cmpa)->next && check_next((*cmpa)))
	{
		if (!*c && ((*cmpa)->tok == d_quote || (*cmpa)->tok == s_quote
				|| (*cmpa)->next->tok == d_quote
				|| (*cmpa)->next->tok == s_quote))
			*c = true;
		(*cmpa)->data = join_quotes((*cmpa), (*cmpa)->next);
		ft_comp_n_del(&(*cmpa), (*cmpa)->next, *c);
	}
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
