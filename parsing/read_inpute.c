/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inpute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:55:39 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/02 11:18:23 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*get_command(t_list **prime, t_comp **cmpa, t_env *env)
{
	t_cmd	*cmd;
	char	*line;

	cmd = NULL;
	while (true)
	{
		line = m_readline();
		if (!line)
			return (NULL);
		if (*line)
		{
			disperse(line, prime);
			free(line);
			if (check_quotes(*prime))
			{
				if (prs(prime, cmpa, env))
					if (cmd_struct_fill(*cmpa, &cmd))
						return (ft_comp_clear(cmpa, 1), cmd);
				ft_comp_clear(cmpa, 0);
			}
			else
			{
				write(2, "syntax error unclosed quote\n", 29);
				g_exit_status = 1;
			}
			ft_lstclear(prime, free);
		}
		else
			free(line);
	}
}

char	*m_readline(void)
{
	char	*line;
	char	*tmp;

	tmp = readline ("minishell 👽$ ");
	add_history(tmp);
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}

bool	prs(t_list **prime, t_comp **cmpa, t_env *env)
{
	types_separation(*prime, cmpa);
	here_doc_processes(*cmpa);
	replace_line(*cmpa, env);
	trim_quotes(*cmpa);
	ft_lstclear(prime, free);
	if (!open_here_doc(*cmpa, env))
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
	i = -1;
	while (line[++i])
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
