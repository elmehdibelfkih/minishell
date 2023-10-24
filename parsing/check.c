/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:05 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/24 19:25:32 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_quotes(t_list *prime)
{
	char	*c;

	while (prime)
	{
		c = (char *)prime->content;
		if ((c[0] == '\'' && c[ft_strlen(c) - 1] != '\'')
			|| (c[0] == '\'' && ft_strlen(c) == 1))
			return (false);
		else if ((c[0] == '\"' && c[ft_strlen(c) - 1] != '\"')
			|| (c[0] == '\"' && ft_strlen(c) == 1))
			return (false);
		else
			prime = prime->next;
	}
	return (true);
}

bool	check_next(t_comp *cmpa)
{
	if (cmpa->next && (cmpa->next->tok == d_quote
			|| cmpa->next->tok == s_quote
			|| cmpa->next->tok == word || cmpa->next->tok == delimiter))
		return (true);
	return (false);
}

void	ft_comp_n_del(t_comp **cmpa, t_comp *next, bool c)
{
	t_comp	*tmp;

	if (c)
		(*cmpa)->expanded = false;
	tmp = next->next;
	free(next);
	(*cmpa)->next = tmp;
}
