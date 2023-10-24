/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_structuring_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:44:02 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/24 19:11:27 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	types_separation_pipe_space(t_comp **cmpa, char *tmp, t_list *prime)
{
	int		i;
	void	*t;

	i = 0;
	if (*tmp == ' ')
	{
		while (tmp[i] == ' ')
			i++;
		t = (void *)ft_substr(tmp, i, INT_MAX);
		free(prime->content);
		prime->content = t;
		ft_comp_add_back(cmpa, ft_compnew(NULL, space, false));
		if (!*(char *)(prime->content))
			return (true);
	}
	else
	{
		t = (void *)ft_substr(tmp, 1, INT_MAX);
		free(prime->content);
		prime->content = t;
		ft_comp_add_back(cmpa, ft_compnew("|", pipe_op, false));
		if (!*(char *)(prime->content))
			return (true);
	}
	return (false);
}

t_comp	*ft_compnew(char *data, t_component	tok, bool expanded)
{
	t_comp	*new;

	new = (t_comp *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = data;
	new->expanded = expanded;
	new->tok = tok;
	new->next = NULL;
	return (new);
}

void	ft_comp_add_back(t_comp **head, t_comp *new)
{
	t_comp	*p;

	if (!new)
		return ;
	if (*head == NULL)
	{
		if (!(*head))
			new->next = NULL;
		if (!new)
			return ;
		new->next = *head;
		*head = new;
	}
	else
	{
		p = ft_comp_last(*head);
		p->next = new;
	}
}

t_comp	*ft_comp_last(t_comp *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	ft_comp_clear(t_comp **head, int i)
{
	t_comp	*t;

	t = *head;
	if (!*head)
		return ;
	while (*head)
	{
		if (i == 0 && ((*head)->tok == word || (*head)->tok == s_quote
				|| (*head)->tok == d_quote || (*head)->tok == delimiter))
		{
			free((*head)->data);
			(*head)->data = NULL;
		}
		t = (*head)->next;
		free(*head);
		*head = t;
	}
}
