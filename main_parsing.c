/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/07 21:37:20 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	
	(void)ac;
	(void)av;
	// (void)envp;
	t_env *head;
	t_env *tmp;

	get_line();
	head = ft_get_env(envp);
	tmp = head;
	while (tmp->next)
	{
		printf("%s  ==>   %s\n", tmp->name , tmp->data);
		tmp = tmp->next;
	}
	ft_envclear(&head);
}
