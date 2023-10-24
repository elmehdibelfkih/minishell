/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/23 17:22:37 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	t_list *prime;
	t_list *tmp;
	t_comp *cmpa;
	t_env *env;
	t_cmd	*cmd;
	// int br;
	char *c;
	int i;

	i = -1;
	c = NULL;
	prime = NULL;
	cmpa = NULL;
	cmd = NULL;
	env = ft_get_env(envp);
	cmd = get_command(&prime, &cmpa, env);

	execute(&cmd, &env);
	// while (true)
	// {
		// br = read(cmd->inp, c, 100);
		// printf("%d\n", br);
		// if(br == -1)
		// 	break;
		// write(cmd->out, c, br);
		// write(cmd->inp, "wafiiiiiin azabi \n", 19);
		
	// }
	// while (cmd)
	// {
	// 	i = -1;
	// 	while (cmd->cmd[++i])
	// 		printf("cmd : %s\n",cmd->cmd[i]);
	// 	printf("input  : %d\n", cmd->inp);
	// 	printf("output : %d\n", cmd->out);
	// 	printf("+================+\n");
	// 	cmd = cmd->next;
	// }
	tmp = prime;
	ft_lstclear(&tmp, free);
	// printf("%s\n", replace_var("mehdi $USdER 1337", env));
}
