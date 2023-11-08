/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:48:12 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/09 00:14:31 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	m_cd(t_cmd *cmd, t_env **env)
{
	char	*path;
	char	*t;

	if (!cmd->cmd[1])
		return ;
	up_date_pwd(env, pwd(false, 0, *env), true);
	path = join_path(cmd->cmd[1], *env, 1);
	t = join_path(cmd->cmd[1], *env, 0);
	if (m_cd_assistant(t, path, env))
		return (free (path), free (t));
	else if (m_cd_assistant_1(t, path, env))
		return (free (path), free (t));
	else 
		m_cd_assistant_2(t, path, env);
}

bool	m_cd_assistant_1(char *t, char *path, t_env **env)
{
	char	*newpath;

	if (!ft_strncmp(t, "..", INT_MAX) && chdir(t))
	{
		newpath = ft_strjoin(path, "/");
		free (path);
		path = ft_strjoin(newpath, "..");
		free(newpath);
		if (!o_pwd(*env))
			return (ft_env_add_back(env, ft_envnew(NULL, ft_strdup(path))),
				free (path), free (t),
				up_date_pwd(env, pwd(false, 0, *env), false), true);
		free(o_pwd(*env)->data);
		o_pwd(*env)->data = ft_strdup(path);
		return (free (path), free (t),
			up_date_pwd(env, pwd(false, 0, *env), false), true);
	}
	return (false);
}

bool	m_cd_assistant(char *t, char *path, t_env **env)
{
	if (!chdir(path))
	{
		if (!o_pwd(*env))
		{
			ft_env_add_back(env, ft_envnew(NULL, ft_strdup(path)));
			return (up_date_pwd(env, pwd(false, 0, *env), false), true);
		}
		free(o_pwd(*env)->data);
		o_pwd(*env)->data = ft_strdup(path);
		return (up_date_pwd(env, pwd(false, 0, *env), false), true);
	}
	else if (ft_strncmp(t, ".", 1) && !chdir(t))
	{
		if (!o_pwd(*env))
		{
			ft_env_add_back(env, ft_envnew(NULL, ft_strdup(t)));
			return (up_date_pwd(env, pwd(false, 0, *env), false), true);
		}
		free(o_pwd(*env)->data);
		o_pwd(*env)->data = ft_strdup(t);
		return (up_date_pwd(env, pwd(false, 0, *env), false), true);
	}
	return (false);
}

void	m_cd_assistant_2(char *t, char *path, t_env **env)
{
	if (!ft_strncmp(t, "..", INT_MAX))
	{
		g_exit_status = 1;
		write(2, "minishell: cd: ", 16);
		perror("..");
		if (!o_pwd(*env))
		{
			ft_env_add_back(env, ft_envnew(NULL, ft_strdup(path)));
			return (up_date_pwd(env, pwd(false, 0, *env), false),
				free (path), free (t));
		}
		free(o_pwd(*env)->data);
		o_pwd(*env)->data = ft_strdup(path);
		return (free (path), free (t));
	}
	g_exit_status = 1;
	write(2, "minishell: cd: ", 16);
	perror(t);
	return (up_date_pwd(env, pwd(false, 0, *env), false),
		free (path), free (t));
}

char	*join_path(char *dir, t_env *env, bool p)
{
	char	*path;
	char	*newpath;
	char	*t;

	if (dir[ft_strlen(dir) - 1] == '/')
		t = ft_substr(dir, 0, ft_strlen(dir) - 1);
	else
		t = ft_strdup(dir);
	if (!p)
		return (t);
	path = pwd(false, 0, env);
	newpath = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(newpath, t);
	free (newpath);
	free (t);
	return (path);
}
