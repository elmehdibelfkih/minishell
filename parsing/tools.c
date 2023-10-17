/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:02:49 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/17 08:26:49 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_message(int i)
{
	if (i == 1)
		perror("malloc failed");
	else if (i == 2)
		perror("pipe failed");
	else if (i == 3)
		perror("fork failed");
	exit(EXIT_FAILURE);
}