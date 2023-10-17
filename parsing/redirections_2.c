/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:42:09 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/17 13:47:46 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*redir_fill(t_comp *cmpa)
{
	t_redir	*red;

	red = NULL;
	while (cmpa && cmpa->tok != pipe_op)
	{
		if (cmpa->next->tok == r_inp || cmpa->next->tok == r_out
			|| cmpa->next->tok == app_op)
		;
		else
			cmpa = cmpa->next;
	}
	return (red);
}
