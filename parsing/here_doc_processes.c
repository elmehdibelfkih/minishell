/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:48:59 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/07 11:54:08 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_processes(t_comp *cmpa)
{
	bool	c;
	t_comp	*tmp;

	tmp = cmpa;
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
	if (!here_doc_processes_assistant_2(cmpa))
		return ;
	if ((*cmpa)->tok != pipe_op && (*cmpa)->tok != r_inp 
		&& (*cmpa)->tok != r_out && (*cmpa)->tok != app_op 
		&& (*cmpa)->tok != here_doc)
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

bool	here_doc_processes_assistant_2(t_comp **cmpa)
{
	char	*tmp;

	if ((*cmpa)->next && (*cmpa)->next->tok == here_doc)
		return (false);
	if ((*cmpa)->next)
		(*cmpa) = (*cmpa)->next;
	if ((*cmpa)->next && ((*cmpa)->tok == space))
		(*cmpa) = (*cmpa)->next;
	if ((*cmpa)->tok == word)
		(*cmpa)->expanded = true;
	if ((*cmpa)->tok == s_quote || (*cmpa)->tok == d_quote)
	{
		if ((*cmpa)->tok == s_quote)
			tmp = ft_strtrim((*cmpa)->data, "\'");
		else
			tmp = ft_strtrim((*cmpa)->data, "\"");
		free ((*cmpa)->data);
		(*cmpa)->data = tmp;
		(*cmpa)->tok = delimiter;
		(*cmpa)->expanded = false;
	}
	return (true);
}

bool	open_here_doc(t_comp *cmpa, t_env *env)
{
	int	fd;

	while (cmpa)
	{
		if (cmpa->tok == here_doc)
		{
			if (!cmpa->next)
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				return (g_exit_status = 258, false);
			}
			else if (cmpa->next->tok != delimiter)
			{
				perr("syntax error near unexpected token ", cmpa->next->data);
				return (g_exit_status = 258, false);
			}
			fd = new_fork(cmpa->next->data, cmpa->next->expanded, env);
			cmpa->next->fd = fd;
		}
		cmpa = cmpa->next;
	}
	return (true);
}
