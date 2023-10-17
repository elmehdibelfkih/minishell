/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_struct_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:45:27 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/17 13:46:43 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	nb_cmd(t_comp *cmpa)
{
	size_t	i;

	i = 0;
	while (cmpa && cmpa->tok != pipe_op)
	{
		if (cmpa->tok == word)
			i++;
		else
			cmpa = cmpa->next;
	}
	return (i);
}
