/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:31:37 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/09 12:52:34 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	if (!env)
		return (NULL);
	len = size_env(env);
	arr = malloc(sizeof(char *) * (len + 2));
	if (!arr)
		return (NULL);
	len = -1;
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
