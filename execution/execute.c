/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:32:35 by ybouchra          #+#    #+#             */
/*   Updated: 2023/10/24 18:53:14 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	exec_cmd(t_cmd *commands, char *path)
{
	int inp;
	int out;

	inp = commands->inp;
	out = commands->out;
	if (inp > -1 || out > -1)
		execve(path, commands->cmd, NULL);
		perror("minishell: execve");
		exit(1);
}

int  check_redir(t_cmd *commands)
{
	int inp;
	int out;

	inp = commands->inp;	
	out = commands->out;
	if ((out > -1 || inp > -1) && (out != 1 || inp != 0))
	{
		if (out != 1)
			dup2(out, 1);
		if (inp != 0)
			dup2(inp, 0);
		return(1);
	}
	return(0);
}

void	_cmds(char **paths, t_cmd *commands)
{
	pid_t pid;
	int fd[2];
	char *path;

	int inp = dup(0), out = dup(1);
	while (commands)
	{
		path = find_path(paths, commands);
		if (!path)
			return(ft_err(commands));
		printf("redir ---->%d\n", check_redir(commands));
	
		if (commands->next)
		{
			if (pipe(fd) == -1)
			{
				perror("minishell: pipe");
				exit(1);
			}
		}
		if ((pid = fork()) == -1)
		{
			perror("minishell: fork");
			exit(1);
		}
		if (pid == 0)
		{
			if (commands->next)
			{
				close(fd[0]);
				dup2(fd[1], 1);
			}
			exec_cmd(commands, path);
		}
		else
		{
			wait(NULL);
			if (commands->next)
			{
				close(fd[1]);
				dup2(fd[0], 0);
			}
		}
		free(path);
		commands = commands->next;
	}
	(dup2(out, 1), dup2(inp, 0));
	(close(out), close(inp));
	return;
}

void execute(t_cmd **commands, t_env **env)
{
	char **paths;
	paths = get_paths(*env, "PATH");
	if (!paths)
		write(1, "1_No such file or directory\n", 28);
	// if(!ft_exec_cmd(paths, *commands))
	// 	write(1,"2_No such file or directory\n", 28);

	_cmds(paths, *commands);
}