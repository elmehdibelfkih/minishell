/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:48:12 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/07 11:57:17 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	m_cd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	*newpath;
	char	*t;

	if (!cmd->cmd[1])
		return ;
	path = join_path(cmd->cmd[1], env, 1);
	t = join_path(cmd->cmd[1], env, 0);
	if (!chdir(path))
	{
		printf("hi 1 \n");
		if (!o_pwd(env))
		{
			ft_env_add_back(&env, ft_envnew(NULL, ft_strdup(path)));
			return ;
		}
		free(o_pwd(env)->data);
		o_pwd(env)->data = ft_strdup(ft_strdup(path));
		free (t);
		return ;
	}
	else if (ft_strncmp(t, "..", INT_MAX) && !chdir(t))
	{
		printf("hi 2 \n");
		if (!o_pwd(env))
		{
			printf("%s\n", t);
			ft_env_add_back(&env, ft_envnew(NULL, ft_strdup(t)));
			return ;
		}
		free(o_pwd(env)->data);
		o_pwd(env)->data = ft_strdup(ft_strdup(t));
		printf("%s\n", t);
		free (t);
		return ;
	}
	else if (!ft_strncmp(t, "..", INT_MAX) && chdir(t))
	{
		perror("cd : ");
		printf("hi 3 \n");
		newpath = ft_strjoin(path, "/");
		free (path);
		path = ft_strjoin(newpath, "..");
		if (!o_pwd(env))
		{
			ft_env_add_back(&env, ft_envnew(NULL, ft_strdup(path)));
			return ;
		}
		free(o_pwd(env)->data);
		o_pwd(env)->data = ft_strdup(ft_strdup(path));
		perror("cd : ");
		return ;
	}
	else
	{
		printf("hi 4 \n");
		if (!ft_strncmp(t, "..", INT_MAX))
		{
			perror("cd : ");
			if (!o_pwd(env))
			{
				ft_env_add_back(&env, ft_envnew(NULL, ft_strdup(path)));
				perror("cd : ");
				return ;
			}
			free(o_pwd(env)->data);
			o_pwd(env)->data = ft_strdup(ft_strdup(path));
			return ;
		}
		perror("cd : ");
		return ;
	}
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
