/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:31:37 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/08 19:21:12 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_err_std(t_cmd *command)
{
	if (command->cmd[0])
	{
		write(2, "minishell : ", 13);
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": command not found\n", 21);
		g_exit_status = 127;
		exit(127);
	}
}

void	checker_1(t_cmd *command, char *cmd)
{
	if (cmd[0] == '.' && !cmd[1])
		ft_err_2(command);
	if (cmd[0] == '/' && !cmd[1])
		ft_err_126(command);
	if ((cmd[0] == '.' && cmd[1] == '.') && !cmd[2])
		ft_err_std(command);
	if (cmd[0] == '/' && cmd[1] == '/' && !cmd[2])
		ft_err_126(command);
	if (cmd[0] == '.' && cmd[1] == '/' && (!cmd[2] || cmd[2] == '.'))
		ft_err_126(command);
	if (cmd[0] == '/' && cmd[1] == '.' && !cmd[2])
		ft_err_126(command);
}

int	size_env(t_env *env)
{
	int		len;

	len = 0;
	if (!env)
		return (0);
	while (env)
	{
		env = env->next;
		len++;
	}
	return (len);
}

char	**list_to_tab(t_env *env)
{
	char	*name;
	char	**arr;
	int		len;
	t_env	*tmp;

	tmp = env;
	len = size_env(env);
	arr = malloc(sizeof(char *) * len + 1);
	if (!arr)
		return (NULL);
	len = -1;
	env = tmp;
	while (env)
	{
		name = ft_strjoin(env->name, "=");
		arr[++len] = ft_strjoin(name, env->data);
		free(name);
		env = env->next;
	}
	arr[++len] = NULL;
	return (arr);
}
