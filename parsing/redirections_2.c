/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:42:09 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/18 13:12:08 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*redir_fill(t_comp *cmpa)
{
	t_redir	*red;

	red = NULL;
	// if (cmpa->tok == pipe_op)
	// 	cmpa = cmpa->next;
	while (cmpa && cmpa->tok != pipe_op)
	{
		if (cmpa->next && (cmpa->next->tok == r_inp || cmpa->next->tok == r_out
			|| cmpa->next->tok == app_op))
		{
			ft_redir_add_back(&red, ft_redirpnew
				(cmpa->next->next->data, 0, cmpa->next->tok));
			ft_comp_nd_del(&cmpa, cmpa->next);
			ft_comp_nd_del(&cmpa, cmpa->next);
		}
		else
			cmpa = cmpa->next;
	}
	return (red);
}

bool	inp_red(t_redir	*red, t_cmd	*cmd, t_list *here_doc_fd)
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
				cmd->inp = ou_fd;
		}
		red = red->next;
	}
	return (true);
}

int	get_fd(t_list *here_doc_fd)
{
	static int	i;
	int			j;

	j = 0;
	while(j != i)
	{
		here_doc_fd = here_doc_fd->next;
		j++;
	}
	i++;
	j = *(int *)(here_doc_fd->content);
	return (j);
}