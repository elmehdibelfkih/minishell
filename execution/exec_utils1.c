/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:03:56 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/05 18:25:18 by ybouchra         ###   ########.fr       */
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

char *valid_cmd(char *cmd)
{
	int	 i;

	i = 0;
	if(!cmd)
		return (NULL);
	
	if(cmd[i] && cmd[i] == '/')
	{
		while (cmd[i] == '/' && cmd[i + 1])
			i++;
		return(ft_strjoin("/" ,cmd + i));
	}
	return(NULL);

}

int	is_directory(char *cmd, char **paths)
{
	int	i;
	char *tmp;
	
	i = -1;
	
	tmp = valid_cmd(cmd);
	while(paths[++i])
	{	
		if (!ft_strncmp(tmp, paths[i], ft_strlen(tmp)))
				return(free(tmp),1);
	}
	return(free(tmp), 0);
}