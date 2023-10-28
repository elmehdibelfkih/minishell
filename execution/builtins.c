/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:12:16 by ybouchra          #+#    #+#             */
/*   Updated: 2023/10/28 02:50:15 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int _env(t_cmd *command, int tmp_env)
// {


// 		if (!ft_strncmp(command->cmd[0], "env", INT_MAX))
// 		{
// 			while(env)
// 			{
// 				printf("%s=%s\n",env->name, env->data);
// 				tmp_env = env->next;
// 			}
// 			return(1);
// 		}
// 		return(0);
// }

int  _unset(t_cmd *commands, t_env *env)
{
	t_env *next_env;

			while(env)
			{
				if(!ft_strncmp(env->next->name, commands->cmd[1], INT_MAX))
					{
						next_env = env->next->next;
						env->next = next_env;
						
					}
				env = env->next;
		}
	return(0);

}