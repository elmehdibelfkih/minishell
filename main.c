/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/28 16:55:37 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f()
{
	system("leaks minishell");
}


void		handle_sigint(int sig)
{	
	(void)sig;
	// printf("%d\n", sig);
	if(sig == SIGINT)
	{
		printf(" CTR + C\n");
		exit(0);
	}	

}

int		handle_sigQ(int sig)
{	
		(void)sig;
	// printf("%d\n", sig);
	// if(sig == SIGQUIT)
		printf(" CTR + /\n");
	return (1);
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
		signal(SIGINT, handle_sigint);
	// while (true)
	// {

		// signal(SIGTERM, handle_sigQ);
		cmd = get_command(&prime, &cmpa, env);
		execute(&cmd, &env);
		ft_cmd_clear(&cmd);
	// }
}
