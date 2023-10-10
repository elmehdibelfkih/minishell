/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/10 20:17:18 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	
	(void)ac;
	(void)av;
	(void)envp;
	t_list *prime;
	// t_env *env;
	
	// env = ft_get_env(envp);
	prime = NULL;
	get_line(&prime);
	// tmp = prime;
	// while (env)
	// {
	// 	printf("%s > %s\n", env->name, env->data);
	// 	env = env->next;
	// }
	// ft_lstclear(&tmp, free);
}
