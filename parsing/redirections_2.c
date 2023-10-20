/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:42:09 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/20 18:41:06 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*redir_fill(t_comp *cmpa)
{
	t_redir	*red;

	red = NULL;
	while (cmpa && cmpa->tok != pipe_op)
	{
		if (cmpa && (cmpa->tok == r_inp || cmpa->tok == r_out
				|| cmpa->tok == app_op || cmpa->tok == here_doc))
		{
			if (cmpa->tok == here_doc)
				ft_redir_add_back(&red, ft_redirpnew
					(cmpa->next->data, cmpa->next->fd, cmpa->tok));
			else
				ft_redir_add_back(&red, ft_redirpnew
					(cmpa->next->data, 0, cmpa->tok));
		}
		cmpa = cmpa->next;
	}
	return (red);
}

int	inp_red(t_redir	*red)
{
	int	in_fd;
	in_fd = 0;
	while (red)
	{
		if (red->tok == r_inp || red->tok == here_doc)
		{
			if (in_fd != 0)
				close(in_fd);
			if (red->tok == r_inp)
				in_fd = open(red->f_name, O_RDONLY, 0777);
			else
				in_fd = red->fd;
			if (in_fd == -1)
			{
				printf("%s: No such file or directory\n", red->f_name);
				return (-1);
			}
		}
		red = red->next;
	}
	return (in_fd);
}

int	out_red(t_redir	*red)
{
	int	ou_fd;

	ou_fd = 1;
	while (red)
	{
		if (red->tok == r_out || red->tok == app_op)
		{
			if (ou_fd != 1)
				close (ou_fd);
			if (red->tok == r_out)
				ou_fd = open(red->f_name, O_WRONLY | O_CREAT, 0777);
			else
				ou_fd = open(red->f_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (ou_fd == -1)
			{
				printf("%s: No such file or directory\n", red->f_name);
				return (-1);
			}
		}
		red = red->next;
	}
	return (ou_fd);
}

int	get_fd(t_list *here_doc_fd)
{
	static int	i;
	int			j;

	j = 0;
	while (here_doc_fd && j != i)
	{
		here_doc_fd = here_doc_fd->next;
		j++;
	}
	i++;
	j = *((int *)(here_doc_fd->content));
	return (j);
}
