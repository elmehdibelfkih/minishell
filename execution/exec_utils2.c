/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:11:40 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/01 12:31:38 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
