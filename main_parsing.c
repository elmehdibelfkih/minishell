/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/19 08:36:43 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	
	(void)ac;
	(void)av;
	// (void)envp;
	t_list *prime;
	t_list *tmp;
	t_comp *cmpa;
	t_env *env;
	t_cmd	*cmd;
	prime = NULL;
	cmpa = NULL;
	cmd = NULL;
	env = ft_get_env(envp);
	get_line(&prime, &cmpa, env, &cmd);
	tmp = prime;
	ft_lstclear(&tmp, free);
	// printf("%s\n", replace_var("mehdi $USdER 1337", env));
}
