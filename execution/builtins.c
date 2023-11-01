/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:12:16 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/01 08:26:21 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_delone(t_env **env, char *target)
{
	t_env	*temp;
	t_env	*current;

	current = *env;
	if (!env || !*env)
		return ;
	if (!ft_strncmp((*env)->name, target, INT_MAX))
	{
		temp = *env;
		(*env) = (*env)->next;
		return (free(temp->data), free(temp->name), free(temp));
	}
	while (current)
	{
		if (current && current->next && !ft_strncmp
			((current)->next->name, target, INT_MAX))
		{
			temp = (current)->next;
			(current)->next = (current)->next->next;
			free(temp->data);
			free(temp->name);
			free(temp);
			temp = NULL;
			return ;
		}
		current = (current)->next;
	}
}

int	_unset(t_cmd *commands, t_env **env)
{
	int	i;

	i = 0;
	if (commands->cmd[1] == NULL)
		return (write(2, "unset: not enough arguments\n", 29), 0);
	while (commands->cmd[++i])
		env_delone(env, commands->cmd[i]);
	return (1);
}
