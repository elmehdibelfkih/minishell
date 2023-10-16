/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inpute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:55:39 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/16 10:58:34 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_line(t_list **prime, t_comp **cmpa, t_env *env)
{
	char	*line;
	char	*tmp;

	while (true)
	{
		tmp = readline ("minishell : ");
		add_history(tmp);
		rl_on_new_line();
		rl_redisplay();
		if (*tmp)
		{
			line = ft_strtrim(tmp, " ");
			free(tmp);
			disperse(line, prime);
			free(line);
			if (check_quotes(*prime))
			{
				types_separation(*prime, cmpa);
				here_doc_processes(*cmpa);
				replace_line(*cmpa, env);
				trim_quotes(*cmpa);
				open_here_doc(*cmpa, env);
				if (!check_files(*cmpa))
					printf("makhdamch hadchi\n");
				while (*cmpa)
				{
					printf("%s     %d\n", (*cmpa)->data, (*cmpa)->tok);
					if ((*cmpa)->expanded)
						printf("expanded\n");
					*cmpa = (*cmpa)->next;
					printf("==================================================\n");
				}
			}
			else
				printf("syntax error : unclosed quote\n");
			ft_lstclear(prime, free);
			ft_comp_clear(cmpa);
		}
	}
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
