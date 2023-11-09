/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_struct_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:45:27 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/09 13:29:41 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	nb_cmd(t_comp *cmpa)
{
	size_t	i;

	i = 0;
	while (cmpa && cmpa->tok != pipe_op)
	{
		if (cmpa && (cmpa->tok == r_inp || cmpa->tok == r_out
				|| cmpa->tok == app_op || cmpa->tok == here_doc))
			cmpa = cmpa->next->next;
		if (cmpa)
			i++;
		if (cmpa)
			cmpa = cmpa->next;
	}
	return (i);
}

bool	cmd_struct_fill(t_comp *cmpa, t_cmd **cmd)
{
	t_redir		*red;
	char		**com;
	int			in_fd;
	int			ou_fd;

	while (cmpa)
	{
		com = cmd_fill(cmpa);
		red = redir_fill(cmpa);
		in_fd = inp_red(red);
		if (in_fd != -1)
			ou_fd = out_red(red);
		ft_redir_clear(&red);
		ft_cmd_add_back(cmd, ft_cmdnew(com, in_fd, ou_fd));
		while (cmpa && cmpa->tok != pipe_op)
			cmpa = cmpa->next;
		if (cmpa && cmpa->tok == pipe_op)
			cmpa = cmpa->next;
	}
	return (true);
}

char	**cmd_fill(t_comp *cmpa)
{
	int			i;
	char		**com;

	i = 0;
	com = (char **)malloc((nb_cmd(cmpa) + 1) * sizeof(char *));
	while (cmpa && cmpa->tok != pipe_op)
	{
		while (cmpa && (cmpa->tok == r_inp || cmpa->tok == r_out
				|| cmpa->tok == app_op || cmpa->tok == here_doc))
			cmpa = cmpa->next->next;
		if (!cmpa || cmpa->tok == pipe_op)
			break ;
		com[i] = cmpa->data;
		i++;
		cmpa = cmpa->next;
	}
	com[i] = NULL;
	return (com);
}
