/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:56 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/23 16:19:33 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_cmdnew(char **cmd, int in_fd, int ou_fd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->inp = in_fd;
	new->out = ou_fd;
	new->next = NULL;
	return (new);
}

void	ft_cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*p;

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
		p = ft_cmd_last(*head);
		p->next = new;
	}
}

t_cmd	*ft_cmd_last(t_cmd *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	ft_cmd_clear(t_cmd **head)
{
	t_cmd	*t;

	t = *head;
	if (!*head)
		return ;
	while (*head)
	{
		ft_clear((*head)->cmd, INT_MAX);
		if ((*head)->inp != 0)
			close((*head)->inp);
		if ((*head)->out != 1)
			close((*head)->out);
		t = (*head)->next;
		free(*head);
		*head = t;
	}
}
