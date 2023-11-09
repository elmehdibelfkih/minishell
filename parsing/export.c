/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 07:36:33 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/09 00:19:36 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_export(t_env *env, int fd)
{
	int	i;

	if (!env)
		return ;
	while (env)
	{
		if (env->name)
			write(fd, "declare -x ", 11);
		i = -1;
		while (env->name && env->name[++i])
			write(fd, &env->name[i], 1);
		if (env->data && env->name)
		{
			write(fd, "=\"", 2);
			i = -1;
			while (env->data && env->data[++i])
				write(fd, &env->data[i], 1);
			write(fd, "\"\n", 2);
		}
		else if (env->name)
			write(fd, "\n", 1);
		env = env->next;
	}
}

void	m_export(t_cmd *cmd, t_env **env, int fd)
{
	int	i;
	int	j;

	i = 1;
	if (!cmd->cmd[1])
		put_export(*env, fd);
	while (cmd->cmd[i])
	{
		j = 0;
		if (ft_isalpha(cmd->cmd[i][j]) || cmd->cmd[i][j] == '_')
		{
			export_assistant(env, cmd->cmd[i], j);
		}
		else
		{
			perr("export: ", cmd->cmd[i]);
			perr("\b\b: not a valid identifier\n", NULL);
			g_exit_status = 1;
		}
		i++;
	}
}

void	export_assistant(t_env **env, char *cmd, int j)
{
	while (cmd[j] && (cmd[j] != '+' && cmd[j] != '='))
	{
		if (!ft_isalnum(cmd[j]) && cmd[j] != '_')
		{
			perr("export: ", cmd);
			perr("\b\b: not a valid identifier\n", NULL);
			g_exit_status = 1;
			return ;
		}
		j++;
	}
	if (cmd[j] == '=')
		new_data(env, ft_substr(cmd, 0, j),
			ft_substr(cmd, j + 1, INT_MAX), false);
	else if (cmd[j] == '+' && cmd[j + 1] != '=')
	{
		perr("export: ", cmd);
		perr("\b\b: not a valid identifier\n", NULL);
		g_exit_status = 1;
	}
	else if (cmd[j] == '+' && cmd[j + 1] == '=')
		new_data(env, ft_substr(cmd, 0, j),
			ft_substr(cmd, j + 2, INT_MAX), true);
	else if (!cmd[j])
		new_data(env, ft_substr(cmd, 0, INT_MAX), NULL, false);
}

void	new_data(t_env **env, char *name, char *data, bool e)
{
	char	*j;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->name && tmp->data && !ft_strncmp(tmp->name, name, INT_MAX))
		{
			if (!data)
				return (free(name));
			if (e == false)
			{
				free(tmp->data);
				tmp->data = data;
				return (free(name));
			}
			j = ft_strjoin(tmp->data, data);
			free (tmp->data);
			tmp->data = j;
			return (free(name), free(data));
		}
		tmp = tmp->next;
	}
	ft_env_add_back(env, ft_envnew(name, data));
}
