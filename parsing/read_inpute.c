/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inpute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:55:39 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/18 13:50:03 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_line(t_list **prime, t_comp **cmpa, t_env *env)
{
	char	*line;
	char	*tmp;
	t_list	*here_doc_fd;
	t_cmd	*cmd;
	int i;
	
	here_doc_fd = NULL;
	cmd = NULL;
	i = 0;
	while (true)
	{
		tmp = readline ("minishell : ");
		add_history(tmp);
		line = ft_strtrim(tmp, " ");
		free(tmp);
		if (line && *line)
		{
			disperse(line, prime);
			free(line);
			if (check_quotes(*prime))
			{
				if (prs(prime, cmpa, env, here_doc_fd))
				{
					cmd_fill(*cmpa, &cmd, here_doc_fd);
					while (cmd)
					{
						while (cmd->cmd[i])
						{
							printf("%s\n", cmd->cmd[i]);
							i++;
						}
						cmd = cmd->next;
					}
					printf("======================================\n");
					while (*cmpa)
					{
						printf ("%s\n", (*cmpa)->data);
						(*cmpa) = (*cmpa)->next;
					}
				}
				ft_lstclear(prime, free);
				ft_comp_clear(cmpa);
			}
			else
				printf("syntax error unclosed quote\n");
			ft_lstclear(prime, free);
			ft_comp_clear(cmpa);
		}
	}
}

bool	prs(t_list **prime, t_comp **cmpa, t_env *env, t_list *here_doc_fd)
{
	types_separation(*prime, cmpa);
	here_doc_processes(*cmpa);
	replace_line(*cmpa, env);
	trim_quotes(*cmpa);
	if (!open_here_doc(*cmpa, env, here_doc_fd))
		return (false);
	if (!check_files(*cmpa))
		return (false);
	return (true);
}

void	disperse(char *line, t_list **prime)
{
	int		start;
	int		i;
	char	c;

	start = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && (line[i] == '\'' || line[i] == '\"'))
		{
			disperse_assistant(line, prime, start, i);
			c = line[i];
			start = i;
			i++;
			while (line[i] && line[i] != c)
				i++;
			ft_lstadd_back(prime,
				ft_lstnew(ft_substr(line, start, i - start + 1)));
			if (!line[i])
				return ;
			start = i;
		}
		i++;
	}
	disperse_assistant(line, prime, start, i);
}

void	disperse_assistant(char *line, t_list **prime, int start, int i)
{
	if (i == 0 && start == 0)
		return ;
	if (start == 0)
		ft_lstadd_back(prime,
			ft_lstnew(ft_substr(line, start, i - start)));
	else
		ft_lstadd_back(prime,
			ft_lstnew(ft_substr(line, start + 1, i - start - 1)));
}

bool	check_quotes(t_list *prime)
{
	char	*c;

	while (prime)
	{
		c = (char *)prime->content;
		if ((c[0] == '\'' && c[ft_strlen(c) - 1] != '\'')
			|| (c[0] == '\'' && ft_strlen(c) == 1))
			return (false);
		else if ((c[0] == '\"' && c[ft_strlen(c) - 1] != '\"')
			|| (c[0] == '\"' && ft_strlen(c) == 1))
			return (false);
		else
			prime = prime->next;
	}
	return (true);
}
