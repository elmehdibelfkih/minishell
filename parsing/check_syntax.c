/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:52:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/09 00:07:51 by ebelfkih         ###   ########.fr       */
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
					perr("syntax error near unexpected token `newline'\n", NULL);
				else
					perr("syntax error near unexpected token ",
						cmpa->next->data);
				return (g_exit_status = 258, false);
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
		perr("syntax error near unexpected token `|'\n", NULL);
		return (g_exit_status = 258, false);
	}
	else if (cmpa && cmpa->tok == pipe_op && !cmpa->next)
	{
		perr("syntax error near unexpected token `newline'\n", NULL);
		return (g_exit_status = 258, false);
	}
	else if (cmpa && cmpa->tok == pipe_op && cmpa->next->tok == pipe_op)
	{
		perr("syntax error near unexpected token `|'\n", NULL);
		return (g_exit_status = 258, false);
	}
	return (true);
}

int	new_fork(char *delim, bool exp, t_env *env)
{
	pid_t	i;
	int		st;
	int		fd[2];

	if (pipe(fd) == -1)
		return (g_exit_status = 1, perror("pipe: "), -1);
	signal(SIGINT, SIG_IGN);
	i = fork();
	if (i == -1)
		return (g_exit_status = 1, perror("pipe: "), -1);
	if (i == 0)
	{
		rl_catch_signals = 1;
		signal(SIGINT, SIG_DFL);
		child_process(delim, exp, env, fd);
	}
	waitpid(i, &st, 0);
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	close(fd[1]);
	if (st == 2)
		return (g_exit_status = 1, close (fd[0]), -1);
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

void	up_date_pwd(t_env **env, char *data, bool o_p)
{
	if (o_p)
		new_data(env, ft_strdup("OLDPWD"), data, false);
	else
		new_data(env, ft_strdup("PWD"), data, false);
	return ;
}
