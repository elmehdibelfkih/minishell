/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:48:12 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/02 11:51:50 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	m_cd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	*newpath;
	char	*u_path;
	char *t;
	
	// chdir("1/2");
	// return ;
	if (!cmd->cmd[1])
		return ;
	if (cmd->cmd[1][ft_strlen(cmd->cmd[1] - 1)] != '/')
		t = ft_strjoin("/", cmd->cmd[1]);
	else
		t = ft_strdup(cmd->cmd[1]);
	path = pwd(false, 0, env);
	// if (!chdir(cmd->cmd[1]))
	// {
	// 	if (!o_pwd(env))
	// 	{
	// 		ft_env_add_back(&env, ft_envnew(NULL, ft_strdup(cmd->cmd[1])));
	// 		return ;
	// 	}
	// 	free(o_pwd(env)->data);
	// 	o_pwd(env)->data = ft_strdup(cmd->cmd[1]);
	// 	free (t);
	// 	return ;
	// }
	newpath = ft_strjoin(path, t);
	free (path);
	free (t);
	u_path = update_path(newpath);
	printf("> %s\n", u_path);
	if (chdir(u_path))
	{
		if (!o_pwd(env))
		{
			ft_env_add_back(&env, ft_envnew(NULL, ft_strdup(newpath)));
			free (newpath);
			return ;
		}
		free(o_pwd(env)->data);
		o_pwd(env)->data = ft_strdup(newpath);
		return ;
	}
}

char	*update_path(char *path)
{
	int	i;
	int	j;
	
	j = 0;
	i = ft_strlen(path);
	while (i > 3)
	{
		if (path[i] == '.' && path[i - 1] == '.' && path[i - 2] == '/')
		{
			i -=3;
			j++;
		}
		i--;
	}
	i = ft_strlen(path) - ((j+1) * 3);
	while(i && j)
	{
		if (path[i] == '/')
		{
			i--;
			while (j && path[i] && path[i] != '/')
				i--;
			j--;
			if (j == 0)
				return (ft_substr(path, 0, i));
		}
		i--;
	}
	return (ft_substr(path, 0, INT_MAX));
}