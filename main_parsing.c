/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/24 05:14:53 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	t_list *prime;
	t_cmd *tmp;
	t_comp *cmpa;
	t_env *env;
	t_cmd	*cmd;
	// int i;

	prime = NULL;
	cmpa = NULL;
	cmd = NULL;
	env = ft_get_env(envp);

	while (true)
	{
		cmd = get_command(&prime, &cmpa, env);
		tmp = cmd;
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
				// char buffer[1024];
				// ssize_t bytes_read;

				// while ((bytes_read = read(cmd->inp, buffer, sizeof(buffer))) > 0) {
				// 	write(1, buffer, bytes_read);
				// }

				// if (bytes_read == -1) {
				// 	perror("read");
				// 	close(cmd->inp);
				// 	exit(EXIT_FAILURE);
				// }
		ft_cmd_clear(&tmp);
	}
}
