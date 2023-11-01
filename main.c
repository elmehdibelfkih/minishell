/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/01 06:40:05 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




int	main(int ac, char **argv, char **envp)
{
	// atexit(f);
	(void)ac;
	(void)argv;
	t_list	*prime;

	t_comp	*cmpa;
	t_env	*env;
	t_cmd	*cmd;

	prime = NULL;
	cmpa = NULL;
	cmd = NULL;
	rl_catch_signals = 0;
	env = ft_get_env(envp);
	
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
	while (true)
	{	
		cmd = get_command(&prime, &cmpa, env);
		if (!cmd)
			break;
		execute(&cmd, &env);
		ft_cmd_clear(&cmd);
	}
}

