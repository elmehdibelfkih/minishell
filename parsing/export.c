/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 07:36:33 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/26 09:34:54 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(t_cmd *cmd, t_env *env, int fd)
{
	int	i;
	int	j;
	int	n;

	i = 1;
	if (!cmd->cmd[1])
		put_export(env, fd);
	while (cmd->cmd[i])
	{
		j = 0;
		if (ft_isalpha(cmd->cmd[i][j]))
		{
			perr("export: ", cmd->cmd[i]);
			perr(": not a valid identifier", NULL);
		}
		else
			while (cmd->cmd[i][j] != '+' || cmd->cmd[i] != '=')
			{
				if (cmd->cmd[i][j] == '+' && cmd->cmd[i][j + 1] != '=')
				{
					perr("export: ", cmd->cmd[i]);
					perr(": not a valid identifier", NULL);
					break ;
				}
				n = j;
				else if (cmd->cmd[i][j] == '=')
				{
					
				}
			}
		i++;
	}
}

void	put_export(t_env *env, int fd)
{
	if (!env)
		return ;
	int	i;

	while (env)
	{
		write(fd, "declare -x ", 12);
		i = -1;
		while (env->name[++i])
			write(fd, &env->name[i], 1);
		write(fd, "=\"", 2);
		i = -1;
		while (env->data[++i])
			write(fd, &env->data[i], 1);
		write(fd, "\"\n", 2);
		env = env->next;
	}
}

char *new_data(t_env *env, char *name, char *data, bool join)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, INT_MAX))
	}
}

// ft_env_add_back(&env,
//     ft_envnew(ft_strdup(spl[0]), ft_strdup(spl[1])));
