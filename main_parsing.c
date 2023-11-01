/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/01 04:41:07 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	t_list	*prime;
	t_cmd	*tmp;
	t_comp	*cmpa;
	t_env	*env;
	t_cmd	*cmd;
	int		i;

	prime = NULL;
	cmpa = NULL;
	cmd = NULL;
	env = ft_get_env(envp);

	while (true)
	{
		cmd = get_command(&prime, &cmpa, env);
		exit_status = 0;
		tmp = cmd;
		while (cmd)
		{
			i = -1;
			if(!check_builtins(cmd, &env))
			{
				while (cmd->cmd[++i])
					printf("cmd : %s\n",cmd->cmd[i]);
			}
			printf("input  : %d\n", cmd->inp);
			printf("output : %d\n", cmd->out);
			printf("+================+\n");
			cmd = cmd->next;
		}
		// printf("%d\n", exit_status);
		ft_cmd_clear(&tmp);
	}
}
