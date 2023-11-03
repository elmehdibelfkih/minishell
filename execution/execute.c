/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:32:35 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/03 03:27:59 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	check_paths(t_cmd *command, char **paths, t_exec_info *exec_info)
{
	exec_info->path = NULL;

	if (!paths || !*paths)
		ft_err_127(command);
	else 
	{
		if (command->cmd[0] && (command->cmd[0][0] == '.' || command->cmd[0][0] == '/') )
			 path_err(command, command->cmd[0]);
		else
		{	
			exec_info->path = absolute_path(paths, command->cmd[0]);
			if (!exec_info->path)
				ft_err_std(command);
		}	
	}
}

void	exec_cmd(t_cmd *command, char **paths,
	t_exec_info *exec_info, t_env *env)
{
	if (command->next)
	{
		close(exec_info->fd[0]);
		dup2(exec_info->fd[1], 1);
		close(exec_info->fd[1]);
	}
	if(command->inp == -1)
		exit(0);
	if (check_builtins(command, &env))
		exit(0);
	check_paths(command, paths, exec_info);
	check_redir(command);
	exec_info->envp = list_to_tab(env);
	if (!execve(exec_info->path, command->cmd, exec_info->envp))
	{
		perror("minishell: execve");
		g_exit_status = 1;
		return (free(exec_info->envp), free(exec_info->path));
	}
}

void exited(void)
{
	    if (WIFEXITED(g_exit_status)) 
		{
            g_exit_status = WEXITSTATUS(g_exit_status);
            printf(" exit_status : %d\n", g_exit_status);
        }
		else if (WIFSIGNALED(g_exit_status)) 
		{
			g_exit_status = WTERMSIG(g_exit_status);
			g_exit_status += 128;
			printf("Child process  exited with status %d\n", g_exit_status) ;
        }
}

void	all_cmds(char **paths, t_cmd *commands,
t_exec_info *exec_info, t_env **env)
{
	while (commands)
	{
		if (commands->next)
			_pipe(exec_info);
		exec_info->pid = fork();
		if (exec_info->pid == -1)
		{
			perror("minishell: fork");
			g_exit_status = 1;
			exit(1);
		}
		if (exec_info->pid == 0)
			exec_cmd(commands, paths, exec_info, *env);
		if (commands->next)
		{
			dup2(exec_info->fd[0], 0);
			(close(exec_info->fd[1]), close(exec_info->fd[0]));
		}
		commands = commands->next;
	}
	reset_fd(exec_info);
	waitpid(exec_info->pid, &g_exit_status, 0);
	while (wait(NULL) > 0)
		;
	exited();
}

void	execute(t_cmd **commands, t_env **env)
{
	char		**paths;
	t_exec_info	exec_info;

	paths = get_paths(*env, "PATH");
	if (!(*commands)->next && check_builtins(*commands, env))
		return ;
	else
	{
		save_fd(&exec_info);
		all_cmds(paths, *commands, &exec_info, env);
	}
	ft_clear(paths, INT_MAX);
}
