/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:12:16 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/01 06:44:37 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_delone(t_env **env, char *target)
{
	t_env	*temp;
	t_env	*current;

	if (!env || !*env)
		return ;
		
		if(!ft_strncmp((*env)->name, target, INT_MAX))
		{
			temp = *env;
				(*env) = (*env)->next;
			printf("%s\n", (*env)->next->name);
			
			return(free(temp->data),free(temp->name),free(temp));
		}
	current = *env;	
		while((*env))
			{
				if(!ft_strncmp(((*env))->next->name, target, INT_MAX))
				{
					temp = ((*env))->next;
					((*env))->next = ((*env))->next->next;
					return(free(temp->data),free(temp->name),free(temp));
				}
				(*env) = ((*env))->next;
			}
}


int  _unset(t_cmd *commands, t_env **env)
{
	int i;

	i	= 0;
	if (!env || !env[0])
	return(0);
	if (commands->cmd[1] == NULL)
		return (write(2, "unset: not enough arguments\n", 29), 0);
	while (commands->cmd[++i])
	{
		// if( is_exist(env,commands->cmd[i]))
		env_delone(env, commands->cmd[i]);
	}
	return (1);
}
