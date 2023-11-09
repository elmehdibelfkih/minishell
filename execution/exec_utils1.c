/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:03:56 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/09 07:50:38 by ybouchra         ###   ########.fr       */
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

char	*valid_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (cmd[i] == '/')
	{
		while (cmd[i] == '/')
			i++;
		i--;
		return (cmd + i);
	}
	return (cmd);
}

int	is_directory(char *cmd, char **paths)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!paths)
		return (0);
	tmp = valid_cmd(cmd);
	while (paths[++i])
	{
		if (!ft_strncmp(tmp, paths[i], ft_strlen(tmp)))
			return (1);
	}
	return (0);
}
