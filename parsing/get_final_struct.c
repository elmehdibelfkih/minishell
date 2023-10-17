/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:56 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/17 13:46:04 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_cmdnew(char **cmd, t_redir *red)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->redir = red;
	new->inp = 0;
	new->out = 1;
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
		t = (*head)->next;
		free(*head);
		*head = t;
	}
}

t_cmd	*cmd_fill(t_comp *cmpa, t_redir *red)
{
	t_cmd	*cmd;
	char	*com;

	cmd = NULL;
	com = (char *)malloc(nb_cmd(cmpa) * sizeof(char *));
}
