/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:21:54 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/08 19:41:22 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_err_127(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 13);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": No such file or directory\n", 29);
		g_exit_status = 127;
		exit(127);
	}
}

void	ft_err_126(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 13);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": is a directory\n", 18);
		g_exit_status = 126;
		exit(126);
	}
}

void	ft_err_std(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 13);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": command not found\n", 21);
		g_exit_status = 127;
		exit(127);
	}
}

void	ft_err_2(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 13);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": filename argument require\n", 29);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": usage: . filename [arguments]\n", 33);
		g_exit_status = 2;
		exit(2);
	}
}

void	ft_err_pd(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 13);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": Permission denied\n", 21);
		g_exit_status = 126;
		exit(126);
	}
}
