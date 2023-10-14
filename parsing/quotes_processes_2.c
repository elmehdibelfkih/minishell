/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_processes_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:55:25 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/14 08:15:26 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    trim_quotes(t_comp *cmpa)
{
    char *tmp;
    t_comp *ctmp;
    t_comp *ctm;

    ctmp = cmpa;
    ctm = cmpa;
    while (cmpa)
	{
		if (cmpa->tok == d_quote || cmpa->tok == s_quote)
		{  
            if (*(cmpa->data) == '\'')
                tmp = ft_strtrim(cmpa->data, "\'");
            else
                tmp = ft_strtrim(cmpa->data, "\"");
            free(cmpa->data);
            cmpa->data = tmp;
            cmpa->tok = word;
		}
		cmpa = cmpa->next;
	}
    join_words(ctmp);
    delete_spaces(ctm);
}

void    join_words(t_comp *cmpa)
{
    while (cmpa)
	{
		if (cmpa->tok == word && check_next(cmpa))
		{
			while (check_next(cmpa))
			{
				cmpa->data = join_quotes(cmpa->data, cmpa->next->data);
				ft_comp_nd_del(&cmpa, cmpa->next);
			}
		}
		else
			cmpa = cmpa->next;
	}
}

void	ft_comp_nd_del(t_comp **cmpa, t_comp *next)
{
	t_comp	*tmp;

	tmp = next->next;
    // free ((*cmpa)->data);
	free(next);
	(*cmpa)->next = tmp;
}

void    delete_spaces(t_comp *cmpa)
{
    while (cmpa)
	{
		if (cmpa->next && cmpa->next->tok == space)
			ft_comp_nd_del(&cmpa, cmpa->next);
		else
			cmpa = cmpa->next;
	}
}