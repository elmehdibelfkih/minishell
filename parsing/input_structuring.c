/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_structuring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:03:26 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/10 22:14:43 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    types_separation(t_list *prime, t_comp *cmpa)
{
    char	*tmp;
	int		i;
	// void	*t;
	bool	c;

	i = 0;
    while (prime)
    {
        tmp = (char *)(prime->content);
        if (*tmp == '\'' || *tmp == '\"')
            c = types_separation_quotes(cmpa, tmp);
        else if (*tmp == ' ' || *tmp == '|')
			c = types_separation_pipe_space(cmpa, tmp, prime);
			
    }
}

bool	types_separation_quotes(t_comp *cmpa, char *tmp)
{
	if (*tmp == '\'')
	{
        ft_comp_add_back(&cmpa, ft_compnew(ft_strdup(tmp), word, false));
		free(tmp);
	}
    else if ((*tmp == '\"') && ft_strchr(tmp, '$'))
	{
        ft_comp_add_back(&cmpa, ft_compnew(ft_strdup(tmp), word, true));
		free(tmp);
		
	}
    else if ((*tmp == '\"') && !ft_strchr(tmp, '$'))
	{
        ft_comp_add_back(&cmpa, ft_compnew(ft_strdup(tmp), word, false));
		free(tmp);	
	}
	return (true);
	
}

bool	types_separation_pipe_space(t_comp *cmpa, char *tmp, t_list *prime)
{
	int		i;
	void	*t;

	i = 0;
	if (*tmp == ' ')
	{
		while (*tmp == ' ')
			i++;
		t = (void *)ft_substr(tmp, i, INT_MAX);
		free(prime->content);
		prime->content = t;
		ft_comp_add_back(&cmpa, ft_compnew(NULL , space, false));
		if (!prime->content)
			return (true);
	}
	else
	{
		t = (void *)ft_substr(tmp, 1, INT_MAX);
		free(prime->content);
		prime->content = t;
		ft_comp_add_back(&cmpa, ft_compnew(NULL , pipe, false));
		if (!prime->content)
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
void	ft_comp_clear(t_comp **head)
{
	t_comp	*t;

	t = *head;
	if (!*head)
		return ;
	while (*head)
	{
		free((*head)->data);
		t = (*head)->next;
		free(*head);
		*head = t;
	}
}
