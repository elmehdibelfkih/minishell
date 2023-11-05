/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/06 00:00:11 by ebelfkih         ###   ########.fr       */
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
	env = ft_get_env(envp);
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (true)
	{
		cmd = get_command(&prime, &cmpa, env);
		if (!cmd)
		{
			write(2, "exit\n", 5);
			break ;
		}
		execute(&cmd, &env);
		ft_cmd_clear(&cmd);
	}
	ft_envclear(&env);
}
