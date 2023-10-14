/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:52:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/14 12:44:02 by ebelfkih         ###   ########.fr       */
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

bool	open_here_doc(t_comp *cmpa)
{
	while (cmpa)
	{
		if (cmpa->tok == here_doc)
		{
			if (!cmpa->next)
				return (false);
			else if (cmpa->next->tok != delimiter)
				return (false);
			else
				new_fork(cmpa->next->data, cmpa->next->expanded);
		}
	}
}

new_fork(char *delim, bool exp)
{
	int		i;
	char	*c;

	i = fork();
	if (i == 0)
	{
		while (true)
		{
			c = readline(">");
			if (exp && ft_strchr(c, '$'))
				// ?????????
				;
		}
	}
}