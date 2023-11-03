/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:21:54 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/02 22:07:11 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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

void	ft_err_126_A(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 12);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": Permission denied\n", 20);
		g_exit_status = 126;
		exit(126);
	}
}
