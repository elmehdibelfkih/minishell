/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:48:10 by ussef             #+#    #+#             */
/*   Updated: 2023/10/30 11:42:31 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[--i] == '/')
		return (1);
	return (0);
}

char	*find_path(char **paths, char *cmd)
{
	char	*line, *tmp_line;
	int		i;

	i = -1;
	if (*cmd && cmd[0] == '.' && cmd[1] == '/' && !access(cmd, X_OK))
		return (cmd);
	while (paths[++i])
	{
		if (verif_path(paths[i]))
		{
			line = ft_strjoin(paths[i], cmd);
			if (!access(line, F_OK))
				return (line);
			free(line);
		}
		else
		{
			tmp_line = ft_strjoin(paths[i], "/");
			line = ft_strjoin(tmp_line, cmd);
			if (!access(line, F_OK))
				return (free(tmp_line), line);
			free(line);
		}
	}
	return (NULL);
}

char	**get_paths(t_env *env, char *s)
{
	char	**paths;

	if(!env)
		return(NULL);
	while (env)
	{
		if (!ft_strncmp(env->name, s, INT_MAX))
		{
			paths = ft_split(env->data, ':');
			return (paths);
		}
		env = env->next;
	}
	return (NULL);
}

void	ft_err_127(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "bash: ", 6);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": command not found\n", 20);
		exit_status = 127;
		return;
	}
}

void	ft_err_1(t_cmd *command)
{
	if (command->cmd[0])
	{
			write(2, "bash: ", 6);
			write(2, command->cmd[0], ft_strlen(command->cmd[0]));
			write(2, " : No such file or directory\n", 30);
			exit_status = 1;
	}
}
