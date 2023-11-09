/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:32:35 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/09 13:42:34 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exited(void)
{
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		g_exit_status = WTERMSIG(g_exit_status);
		g_exit_status += 128;
	}
}

char	*check_paths(t_cmd *command, char **paths, t_exec_info *exec_info)
{
	exec_info->path = NULL;
	if (!paths || !*paths)
		ft_err_127(command);
	else
	{
		if (!command->cmd[0] || !command->cmd[0][0])
			ft_err_std(command);
		path_err_msg(command, command->cmd[0], paths);
		if (command->cmd[0][0] == '.' && command->cmd[0][1] == '/' && 
			!access(command->cmd[0], X_OK))
			return (exec_info->path = command->cmd[0]);
		else if (!is_directory(command->cmd[0], paths) && 
			(is_exist(command->cmd[0], '/')) && !access(command->cmd[0], X_OK))
			return (exec_info->path = command->cmd[0]);
		exec_info->path = absolute_path(paths, command->cmd[0]);
		if (!exec_info->path)
		{
			if (is_exist(command->cmd[0], '/') && access(command->cmd[0], F_OK))
				ft_err_127(command);
			ft_err_std(command);
		}
	}
	return (NULL);
}

void	exec_cmd(t_cmd *command, char **paths,
	t_exec_info *exec_info, t_env *env)
{
	if (command->next)
	{
		close(exec_info->fd[0]);
		dup2(exec_info->fd[1], 1);
	}
	if (command->inp == -1)
		exit(1);
	if (check_builtins(command, &env))
		exit(0);
	check_redir(command);
	check_paths(command, paths, exec_info);
	exec_info->envp = list_to_tab(env);
	if (!execve(exec_info->path, command->cmd, exec_info->envp))
	{
		perror("minishell: execve");
		g_exit_status = 1;
		return (ft_clear(exec_info->envp, INT_MAX), free(exec_info->path));
	}
}

void	all_cmds(char **paths, t_cmd *commands,
	t_exec_info *exec_info, t_env **env)
{
	signal(SIGINT, SIG_IGN);
	while (commands)
	{
		if (commands->next)
			_pipe(exec_info);
		exec_info->pid = fork();
		fork_err(exec_info);
		if (exec_info->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			exec_cmd(commands, paths, exec_info, *env);
		}
		if (commands->next)
		{
			dup2(exec_info->fd[0], 0);
			(close(exec_info->fd[0]), close(exec_info->fd[1]));
		}
		commands = commands->next;
	}
	reset_fd(exec_info);
	waitpid(exec_info->pid, &g_exit_status, 0);
	signal(SIGINT, handle_sigint);
	while (wait(NULL) > 0)
		;
	exited();
}

int	execute(t_cmd **commands, t_env **env)
{
	t_exec_info	exec_info;
	char		**paths;

	paths = get_paths(*env, "PATH");
	if ((!(*commands)->next && check_builtins(*commands, env)))
		return (ft_clear(paths, INT_MAX));
	save_fd(&exec_info);
	all_cmds(paths, *commands, &exec_info, env);
	ft_clear(paths, INT_MAX);
	return (0);
}
