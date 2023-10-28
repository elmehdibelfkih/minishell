/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/28 06:08:46 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f()
{
	system("leaks minishell");
}

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
	env = ft_get_env(envp);

	while (true)
	{
		cmd = get_command(&prime, &cmpa, env);
		execute(&cmd, &env);
		
		ft_cmd_clear(&cmd);
	}
}
