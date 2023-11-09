/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:21:57 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/08 19:47:13 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_start(char **cmd, bool *s)
{
	int	i;
	int	j;

	i = 1;
	*s = true;
	if (!cmd[1])
		return (1);
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j])
		{
			if (i != 1)
				*s = false;
			return (i);
		}
		i++;
	}
	if (i != 1)
		*s = false;
	return (i);
}

void	echo(char **cmd, int fd)
{
	int		i;
	int		j;
	bool	s;

	if (!cmd)
		return ;
	i = echo_start(cmd, &s);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			write(fd, &cmd[i][j], 1);
			j++;
		}
		if (cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (s)
		write(fd, "\n", 1);
	g_exit_status = 0;
}

char	*pwd(bool p, int fd, t_env *env)
{
	int		i;
	char	*path;

	i = -1;
	path = getcwd(NULL, 0);
	if (!path && o_pwd(env))
		path = ft_strdup(o_pwd(env)->data);
	if (p == false)
		return (path);
	while (path && path[++i])
		write(fd, &path[i], 1);
	write(fd, "\n", 1);
	free (path);
	return (NULL);
}

void	env(t_env *env, t_cmd *command, int fd)
{
	int	i;

	if (command->cmd[1] && ft_strncmp(command->cmd[1], "-i", 2))
	{
		write(2, "env: ", 5);
		write(2, command->cmd[1], ft_strlen(command->cmd[1]));
		write(2, ": No such file or directory\n", 28);
		exit(127);
	}
	while (env)
	{
		i = -1;
		if (env->data && env->name)
		{
			while (env->name[++i])
				write(fd, &env->name[i], 1);
			write(fd, "=", 1);
			i = -1;
			while (env->data[++i])
				write(fd, &env->data[i], 1);
			write(fd, "\n", 1);
		}
		env = env->next;
	}
}

t_env	*o_pwd(t_env *env)
{
	while (env)
	{
		if (!env->name)
			return (env);
		env = env->next;
	}
	return (NULL);
}
