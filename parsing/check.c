/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:05 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/09 00:06:57 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

bool	check_next(t_comp *cmpa)
{
	if (cmpa->next && (cmpa->next->tok == d_quote
			|| cmpa->next->tok == s_quote
			|| cmpa->next->tok == word || cmpa->next->tok == delimiter))
		return (true);
	return (false);
}

void	ft_comp_n_del(t_comp **cmpa, t_comp *next, bool c)
{
	t_comp	*tmp;

	if (c)
		(*cmpa)->expanded = false;
	tmp = next->next;
	free(next);
	(*cmpa)->next = tmp;
}

bool	check_builtins(t_cmd *cmd, t_env **envp)
{
	if (!cmd->cmd[0])
		return (false);
	if (!ft_strncmp("echo", cmd->cmd[0], INT_MAX))
		return (echo(cmd->cmd, cmd->out), true);
	else if (!ft_strncmp("pwd", cmd->cmd[0], INT_MAX))
		return (pwd(true, cmd->out, *envp), true);
	else if (!ft_strncmp("env", cmd->cmd[0], INT_MAX))
		return (env(*envp, cmd, cmd->out), true);
	else if (!ft_strncmp("export", cmd->cmd[0], INT_MAX))
		return (m_export(cmd, envp, cmd->out), true);
	else if (!ft_strncmp("unset", cmd->cmd[0], INT_MAX))
		return (_unset(cmd, envp), true);
	else if (!ft_strncmp("exit", cmd->cmd[0], INT_MAX))
		return (__exit(cmd), true);
	else if (!ft_strncmp("cd", cmd->cmd[0], INT_MAX))
		return (m_cd(cmd, envp), true);
	return (false);
}

void	perr(char *str, char *str2)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	if (!str2)
		return ;
	write(2, "`", 1);
	i = -1;
	while (str2[++i])
		write(2, &str2[i], 1);
	write(2, "\'\n", 3);
}
