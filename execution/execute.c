/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:32:35 by ybouchra          #+#    #+#             */
/*   Updated: 2023/10/26 07:32:53 by ybouchra         ###   ########.fr       */
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
			close(out);
		}
		if (inp != 0)
		{
			dup2(inp, 0);
			close(inp);
		}
		return (1);
	}
	return (0);
}

int	_pipe(t_exec_info *exec_info)
{
	if (pipe(exec_info->fd) == -1)
	{
		perror("minishell: pipe");
		exit(1);
	}
	return (0);
}

void	exec_cmd(t_cmd *command, char **paths, t_exec_info *exec_info)
{
	if (command->next)
	{
		close(exec_info->fd[0]);
		dup2(exec_info->fd[1], 1);
	}
	exec_info->path = find_path(paths, command->cmd[0]);
	if (!exec_info->path)
	{
		ft_err(command);
		exit(1);
	}
	check_redir(command);
	execve(exec_info->path, command->cmd, NULL);
	perror("minishell: execve");
	exit(1);
}

void	_cmds(char **paths, t_cmd *commands, t_exec_info *exec_info)
{
	exec_info->def_inp = dup(0);
	exec_info->def_out = dup(1);
	while (commands)
	{
		if (commands->next)
			_pipe(exec_info);
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			exit(1);
		}
		if (pid == 0)
			exec_cmd(commands, paths, exec_info);
		if (commands->next)
		{
			close(exec_info->fd[1]);
			dup2(exec_info->fd[0], 0);
		}
		commands = commands->next;
	}
	(dup2(exec_info->def_out, 1), dup2(exec_info->def_inp, 0));
	(close(exec_info->def_out), close(exec_info->def_inp));
	while (wait(NULL) != -1)
		;
}

void	execute(t_cmd **commands, t_env **env)
{
	t_exec_info	exec_info;
	char		**paths;

	paths = get_paths(*env, "PATH");
	if (!paths)
		write(1, "1_No such file or directory\n", 28);
	_cmds(paths, *commands, &exec_info);
}
