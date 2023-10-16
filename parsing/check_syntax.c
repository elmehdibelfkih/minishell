/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:52:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/16 10:55:27 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_files(t_comp *cmpa)
{
	while (cmpa)
	{
		if (cmpa->tok == redir_input || cmpa->tok == redir_output
			|| cmpa->tok == append_operator)
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

bool	open_here_doc(t_comp *cmpa, t_env *env)
{
	while (cmpa)
	{
		if (cmpa->tok == here_doc)
		{
			if (!cmpa->next)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (false);
			}
			else if (cmpa->next->tok != delimiter)
			{
				printf("syntax error near unexpected token `%s'\n",
					cmpa->next->data);
				return (false);
			}
			new_fork(cmpa->next->data, cmpa->next->expanded, env);
		}
		cmpa = cmpa->next;
	}
	return (true);
}

int	new_fork(char *delim, bool exp, t_env *env)
{
	int		i;
	int		fd;
	char	*c;
	char	*tmp;

	tmp = generate_here_doc_name();
	fd = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0777);
	free(tmp);
	i = fork();
	if (i == 0)
	{
		while (true)
		{
			c = readline("> ");
			if (!ft_strncmp(c, delim, INT_MAX))
				break ;
			while (exp && ft_strchr(c, '$'))
			{
				tmp = replace_var(c, env);
				free(c);
				c = tmp;
			}
			write(fd, c, ft_strlen(c));
			write(fd, "\n", 2);
		}
	}
	return (fd);
}

char	*generate_here_doc_name(void)
{
	static int	i;
	char		*nb;
	char		*name;

	i++;
	nb = ft_itoa(i);
	name = ft_strjoin(".", nb);
	free (nb);
	return (nb);
}
