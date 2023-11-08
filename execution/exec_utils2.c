/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:11:40 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/08 02:07:37 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(t_cmd *commands)
{
	int	inp;
	int	out;

	inp = commands->inp;
	out = commands->out;
	if (out == -1 || inp == -1)
		return (0);
	if (out != 1 || inp != 0)
	{
		if (out != 1)
		{
			dup2(out, 1);
		}
		if (inp != 0)
		{
			dup2(inp, 0);
		}
		if (commands->cmd[0] == NULL)
			exit(0);
		return (1);
	}
	return (0);
}

int	_pipe(t_exec_info *exec_info)
{
	if (pipe(exec_info->fd) == -1)
	{
		perror("minishell: pipe");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	fork_err(t_exec_info *exec_info)
{
	if (exec_info->pid == -1)
	{
		perror("minishell: fork");
		g_exit_status = 1;
		return ;
	}
}

int	is_exist(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	is_end(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	if (s[--i] == c)
		return (1);
	return (0);
}
