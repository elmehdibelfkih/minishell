/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/01 08:54:56 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
	while (true)
	{
		cmd = get_command(&prime, &cmpa, env);
		if (!cmd)
			break ;
		execute(&cmd, &env);
		ft_cmd_clear(&cmd);
	}
}
