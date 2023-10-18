/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_struct_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:45:27 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/18 13:54:51 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	nb_cmd(t_comp *cmpa)
{
	size_t	i;

	i = 0;
	while (cmpa && cmpa->tok != pipe_op)
	{
		if (cmpa->tok == word)
			i++;
		cmpa = cmpa->next;
	}
	return (i);
}

bool	cmd_fill(t_comp *cmpa, t_cmd **cmd, t_list *here_doc_fd)
{
	t_redir	*red;
	t_comp	*tmp;
	char	**com;
	int		i;

	i = 0;
	tmp = cmpa;
	red = redir_fill(cmpa);
	com = (char **)malloc((nb_cmd(cmpa) + 1) * sizeof(char *));
	while (cmpa && cmpa->tok != pipe_op)
	{
		com[i] = cmpa->data;
		cmpa = cmpa->next;
		i++;
	}
	com[i] = NULL;
	ft_cmd_add_back(cmd, ft_cmdnew(com));
	if (!inp_red(red, *cmd, here_doc_fd))
		return (false);
	if (!out_red(red, *cmd))
		return (false);
	ft_redir_clear(&red);
	ft_comp_nds_del(&cmpa);
	return (true);
}

void	ft_comp_nds_del(t_comp **cmpa)
{
	t_comp	**tmp;
	t_comp	**tmp_2;
	t_comp	**tmp_3;

	tmp = cmpa;
	tmp_2 = cmpa;
	tmp_3 = NULL;
	while ((*tmp) && (*tmp)->tok != pipe_op)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->tok == pipe_op)
	{
		(*tmp_3)=(*tmp);
	printf("======================================\n");
		(*tmp) = (*tmp)->next;
		(*tmp_3)->next = NULL;
	}
	(*cmpa) = (*tmp);
	ft_comp_clear(tmp_2);
}

