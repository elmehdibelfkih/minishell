/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/11 18:11:27 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	
	(void)ac;
	(void)av;
	(void)envp;
	t_list *prime;
	t_comp *cmpa;
	// t_env *env;
	
	// env = ft_get_env(envp);
	prime = NULL;
	cmpa = NULL;
	get_line(&prime, &cmpa);
	// tmp = prime;
	// while (env)
	// {
	// 	printf("%s > %s\n", env->name, env->data);
	// 	env = env->next;
	// }
	// ft_lstclear(&tmp, free);
}
