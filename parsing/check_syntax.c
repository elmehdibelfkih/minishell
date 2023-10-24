/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:52:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/24 05:20:45 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_files(t_comp *cmpa)
{
	if (!check_pipe(cmpa, 0))
		return (false);
	while (cmpa)
	{
		if (cmpa && (cmpa->tok == r_inp || cmpa->tok == r_out
				|| cmpa->tok == app_op))
		{
			if (check_next(cmpa))
				cmpa = cmpa->next;
			else
			{
				if (!cmpa->next)
					printf("syntax error near unexpected token `newline'\n");
				else
					printf("syntax error near unexpected token `%s'\n",
						cmpa->next->data);
				return (false); 
			}
		}
		else if (cmpa && cmpa->tok == pipe_op && !check_pipe(cmpa, 1))
			return (false);
		else
			cmpa = cmpa->next;
	}
	return (true);
}

bool	check_pipe(t_comp *cmpa, int i)
{
	if (cmpa && i == 0 && cmpa->tok == pipe_op)
	{
		printf("%s\n", "syntax error near unexpected token `|'");
		return (false);
	}
	else if (cmpa && cmpa->tok == pipe_op && !cmpa->next)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (false);
	}
	else if (cmpa && cmpa->tok == pipe_op && cmpa->next->tok == pipe_op)
	{
		printf("%s\n", "syntax error near unexpected token `|'");
		return (false);
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
				printf("syntax error near unexpected token `newline'\n");
				return (false);
			}
			else if (cmpa->next->tok != delimiter)
			{
				printf("syntax error near unexpected token `%s'\n",
					cmpa->next->data);
				return (false);
			}
			fd = new_fork(cmpa->next->data, cmpa->next->expanded, env);
			cmpa->next->fd = fd;
		}
		cmpa = cmpa->next;
	}
	return (true);
}

int	new_fork(char *delim, bool exp, t_env *env)
{
	pid_t	i;
	int		st;
	int		fd[2];

	if (pipe(fd) == -1)
		return (write(2, "error : pipe\n", 14), -1);
	i = fork();
	if (i == -1)
		return (write(2, "error : fork\n", 14), -1);
	close(fd[1]);
	if (i == 0)
		child_process(delim, exp, env, fd);
	waitpid(i, &st, 0);
	return (fd[0]);
}

void	child_process(char *delim, bool exp, t_env *env, int *fd)
{
	char	*tmp;
	char	*c;
	int		i;

	close(fd[0]);
	while (true) 
	{
		c = readline("> ");
		if (!c)
			exit(1);
		if (c && !ft_strncmp(c, delim, INT_MAX))
			break ;
		i = 0;
		while (c && exp && ft_strchr(c, '$'))
		{
			tmp = replace_var(c, env, &i);
			free(c);
			c = tmp;
		}
		write(fd[1], c, ft_strlen(c));
		write(fd[1], "\n", 1);
		free(c);
	}
	exit(0);
}
