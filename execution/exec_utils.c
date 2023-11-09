/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:48:10 by ussef             #+#    #+#             */
/*   Updated: 2023/11/09 10:13:30 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths(t_env *env, char *s)
{
	char	**paths;

	if (!env)
		return (NULL);
	while (env)
	{
		if (env->data && env->name && !ft_strncmp(env->name, s, INT_MAX))
		{
			paths = ft_split(env->data, ':');
			return (paths);
		}
		env = env->next;
	}
	return (NULL);
}

int	format_path(char *path)
{
	int		i;

	i = 0;
	while (path[i])
		i++;
	if (path[--i] == '/')
		return (1);
	return (0);
}

char	*absolute_path(char **paths, char *cmd)
{
	char	*line;
	char	*tmp_line;
	int		i;

	i = -1;
	while (paths[++i])
	{
		if (format_path(paths[i]))
		{
			line = ft_strjoin(paths[i], cmd);
			if (!access(line, F_OK))
				return (line);
		}
		else
		{
			tmp_line = ft_strjoin(paths[i], "/");
			line = ft_strjoin(tmp_line, cmd);
			if (!access(line, F_OK))
				return (free(tmp_line), line);
		}
		free(line);
	}
	return (NULL);
}

void	path_err_msg(t_cmd *command, char *cmd, char **paths)
{
	if (cmd)
	{
		checker_1(command, cmd);
		if (access(cmd, F_OK))
		{
			if ((cmd[0] == '.' && cmd[1] == '/') || 
				(cmd[0] == '/' && cmd[1] == '.'))
				ft_err_127(command);
			if (cmd && is_end(cmd, '/'))
				ft_err_127(command);
		}
		else
		{
			if (cmd[0] == '/' && is_directory(cmd, paths))
				ft_err_126(command);
			if (cmd[0] == '.' && cmd[1] == '/' && 
				(access(cmd, R_OK) || access(cmd, X_OK) || access(cmd, W_OK)))
				ft_err_pd(command);
			if (cmd && (is_end(cmd, '.') || is_end(cmd, '/')))
				ft_err_127(command);
		}
	}
}
