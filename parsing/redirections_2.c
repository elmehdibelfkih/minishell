/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:42:09 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/19 11:43:06 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*redir_fill(t_comp *cmpa)
{
	t_redir		*red;

	red = NULL;
	while (cmpa && cmpa->tok != pipe_op)
	{
		if (cmpa && (cmpa->tok == r_inp || cmpa->tok == r_out
			|| cmpa->tok == app_op || cmpa->tok == here_doc))
		{
			ft_redir_add_back(&red, ft_redirpnew
				(cmpa->next->data, 0, cmpa->tok));
			// printf("%s\n",cmpa->next->data);
		}
		cmpa = cmpa->next;
	}
	return (red);
}

bool	inp_red(t_redir	*red, t_cmd	*cmd, t_list **here_doc_fd)
{
	int in_fd;

	while (red)
	{
		if (red->tok == r_inp || red->tok == here_doc)
		{
			if (cmd->inp != 0)
				close(cmd->inp);
			if (red->tok == r_inp)
				in_fd = open(red->f_name, O_RDONLY, 0777);
			else
				in_fd = get_fd(here_doc_fd);
			if (in_fd == -1)
			{
				if (cmd->inp != 0)
					close(cmd->inp);
				printf("%s: No such file or directory\n", red->f_name);
				return (false);
			}
			else
				cmd->inp = in_fd;
		}
		red = red->next;
	}
	return (true);
}

bool	out_red(t_redir	*red, t_cmd	*cmd)
{
	int ou_fd;

	while (red)
	{
		if (red->tok == r_out || red->tok == app_op)
		{
			if (cmd->inp != 0)
				close(cmd->inp);
			if (red->tok == r_out)
				ou_fd = open(red->f_name, O_WRONLY | O_CREAT, 0777);
			else
				ou_fd = open(red->f_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (ou_fd == -1)
			{
				if (cmd->inp != 0)
					close(cmd->inp);
				printf("%s: No such file or directory\n", red->f_name);
				return (false);
			}
			else
				cmd->out = ou_fd;
		}
		red = red->next;
	}
	return (true);
}

int	get_fd(t_list **here_doc_fd)
{
	static int	i;
	int			j;

	j = 0;
	while(*here_doc_fd && j != i)
	{
		*here_doc_fd = (*here_doc_fd)->next;
		j++;
	}
	i++;
	j = *((int *)((*here_doc_fd)->content));

	return (j);
}