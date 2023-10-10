/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:55:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/09 20:56:37 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	
	(void)ac;
	(void)av;
	(void)envp;
	t_list *prime;
	t_list *tmp;
	
	prime = NULL;
	get_line(&prime);
	tmp = prime;
	while (prime)
	{
		printf("%s<\n", (char *)prime->content);
		prime = prime->next;
	}
	ft_lstclear(&tmp, free);
}
