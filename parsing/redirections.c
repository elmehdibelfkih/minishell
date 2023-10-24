/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:26:53 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/23 17:26:08 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*ft_redirpnew(char *f_name, int fd, t_component	tok)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->f_name = f_name;
	new->fd = fd;
	new->tok = tok;
	new->next = NULL;
	return (new);
}

void	ft_redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*p;

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
		p = ft_redir_last(*head);
		p->next = new;
	}
}

t_redir	*ft_redir_last(t_redir *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	ft_redir_clear(t_redir **head)
{
	t_redir	*t;

	t = *head;
	if (!*head)
		return ;
	while (*head)
	{
		free((*head)->f_name);
		t = (*head)->next;
		free(*head);
		*head = t;
	}
}
