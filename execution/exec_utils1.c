/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:03:56 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/02 17:36:12 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_fd(t_exec_info *exec_info)
{
	exec_info->def_inp = dup(0);
	exec_info->def_out = dup(1);
}

void	reset_fd(t_exec_info *exec_info)
{
	(dup2(exec_info->def_out, 1), dup2(exec_info->def_inp, 0));
	(close(exec_info->def_out), close(exec_info->def_inp));
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	ft_err_std(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 12);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": command not found\n", 20);
		g_exit_status = 127;
		exit(127);
	}
}
void	ft_err_126(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 12);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": is a directory\n", 17);
		g_exit_status = 126;
		exit(126);
	}
}

void	ft_err_127(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 12);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": No such file or directory\n", 30);
		g_exit_status = 127;
		exit(127);
	}
}
void	ft_err_2(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 12);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": filename argument require\n", 28);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": usage: . filename [arguments]n", 28);
		g_exit_status = 2;
		exit(2);
	}
}
