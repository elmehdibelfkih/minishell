/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:52:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/17 11:48:22 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_files(t_comp *cmpa)
{
	if (!check_pipe(cmpa, 0))
		return (false);
	while (cmpa)
	{
		if (cmpa->tok == r_inp || cmpa->tok == r_out || cmpa->tok == app_op)
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
		else if (!check_pipe(cmpa, 0))
			return (false);
		else
			cmpa = cmpa->next;
	}
	return (true);
}

bool	check_pipe(t_comp *cmpa, int i)
{
	if (i == 0 && cmpa->tok == pipe_op)
	{
		printf("%s\n", "syntax error near unexpected token `|'");
		return (false);
	}
	else if (cmpa->tok == pipe_op && cmpa->next->tok == pipe_op)
	{
		printf("%s\n", "syntax error near unexpected token `|'");
		return (false);
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
	pid_t	i;
	int		st;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_message(2);
	i = fork();
	if (i == -1)
		exit_message(3);
	if (i == 0)
		child_process(delim, exp, env, fd);
	close(fd[1]);
	waitpid(i, &st, 0);
	return (fd[0]);
}

void	child_process(char *delim, bool exp, t_env *env, int *fd)
{
	char	*tmp;
	char	*c;

	close(fd[0]);
	while (true) 
	{
		c = readline("> ");
		if (!c)
			exit(1);
		if (c && !ft_strncmp(c, delim, INT_MAX))
			break ;
		while (c && exp && ft_strchr(c, '$'))
		{
			tmp = replace_var(c, env);
			free(c);
			c = tmp;
		}
		write(fd[1], c, ft_strlen(c));
		write(fd[1], "\n", 2);
		free(c);
	}
	exit(1);
}
