/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:11:40 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/04 09:47:05 by ybouchra         ###   ########.fr       */
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

int	check_redir(t_cmd *commands)
{
	int	inp;
	int	out;

	inp = commands->inp;
	out = commands->out;
	if (out == -1 || inp == -1)
		return (0);
	if (out != 1 || inp != 0)
	{
		if (out != 1)
		{
			dup2(out, 1);
		}
		if (inp != 0)
		{
			dup2(inp, 0);
		}
		return (1);
	}
	return (0);
}

int	_pipe(t_exec_info *exec_info)
{
	if (pipe(exec_info->fd) == -1)
	{
		perror("minishell: pipe");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	is_exist(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}