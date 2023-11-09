/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:22:44 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/09 06:41:05 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_clear(t_env *lst)
{
	free(lst->data);
	free(lst->name);
	free(lst);
	lst = NULL;
}

void	env_delone(t_env **env, char *target)
{
	t_env	*temp;
	t_env	*current;

	if (!env || !env[0])
		return ;
	if (!ft_strncmp((*env)->name, target, INT_MAX))
	{
		temp = *env;
		(*env) = (*env)->next;
		lst_clear(temp);
		return ;
	}
	current = *env;
	while (current)
	{
		if (current && current->next && !ft_strncmp
			((current)->next->name, target, INT_MAX))
		{
			temp = (current)->next;
			(current)->next = (current)->next->next;
			lst_clear(temp);
			return ;
		}
		current = (current)->next;
	}
}

int	_unset(t_cmd *commands, t_env **env)
{
	int	i;

	i = 0;
	while (commands->cmd[++i])
		env_delone(env, commands->cmd[i]);
	g_exit_status = 0;
	return (1);
}
