/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/02 17:40:17 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_sigquit(int pid)
// {
// 	(void)pid;
// 	printf("here");
// 	exit(1);
// }

int	main(int ac, char **argv, char **envp)
{
	t_list	*prime;
	t_comp	*cmpa;
	t_env	*env;
	t_cmd	*cmd;

	(void)ac;
	(void)argv;
	prime = NULL;
	cmpa = NULL;
	cmd = NULL;
	rl_catch_signals = 0;
	env = ft_get_env(envp);
	// signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
	while (true)
	{
		cmd = get_command(&prime, &cmpa, env);
		if (!cmd)
		{
			write(2, "exit ", 5);
			break ;
		}
		execute(&cmd, &env);
		ft_cmd_clear(&cmd);
	}
}
