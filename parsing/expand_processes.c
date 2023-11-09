/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 05:32:03 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/09 15:04:30 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_exp_var(char *line, t_env *env, int *j)
{
	int		i;
	int		start;
	char	*ex;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			start = i;
			i++;
			if (line[i] == '?')
				i++;
			else if (!ft_isalpha(line[i]))
				i++;
			else
				while (line[i] && !ft_strchr(" \'\"$", line[i])
					&& (ft_isalnum(line[i]) || line[i] == '_'))
					i++;
			ex = ft_substr(line, start + 1, i - start - 1);
			return (get_env_var(ex, env, j));
		}
		i++;
	}
	return ("");
}

char	*get_env_var(char *var, t_env *env, int *j)
{
	*j = 0;
	if (var[0] == '?')
		return (free(var), ft_itoa(g_exit_status));
	while (env)
	{
		if (env->name && !ft_strncmp(env->name, var, INT_MAX))
		{
			free(var);
			*j = ft_strlen(env->data);
			return (env->data);
		}
		env = env->next;
	}
	free(var);
	return ("");
}

char	*replace_var_assistant(char *line, char *f, int i)
{
	char	*r;

	i++;
	if (!ft_isalpha(line[i]))
		i++;
	else if (line[i] == '?')
		i++;
	else
		while (line[i] && !ft_strchr(" \'\"$", line[i])
			&& (ft_isalnum(line[i]) || line[i] == '_'))
			i++;
	r = ft_strjoin(f, &line[i]);
	free (f);
	return (r);
}

char	*replace_var(char *line, t_env *env, int *j)
{
	int		i;
	int		e;
	char	*c;
	char	*r;
	char	*f;

	e = 0;
	c = get_exp_var(line + (*j), env, &e);
	i = *j;
	while (line && line[i])
	{
		if (line && line[i] == '$' && line[i + 1])
		{
			r = ft_substr(line, 0, i);
			f = ft_strjoin(r, c);
			if (line[i + 1] && line[i + 1] == '?')
				free(c);
			*j = i + e;
			free (r);
			return (replace_var_assistant(line, f, i));
		}
		i++;
	}
	return (NULL);
}

void	replace_line(t_comp *cmpa, t_env *env)
{
	char	*tmp;
	int		j;

	j = 0;
	while (cmpa)
	{
		if (cmpa->tok != delimiter && cmpa->expanded)
		{
			tmp = replace_var(cmpa->data, env, &j);
			if (tmp)
			{
				free(cmpa->data);
				cmpa->data = tmp;
			}
			if (!tmp || !ft_strchr(tmp, '$'))
				cmpa->expanded = false;
		}
		else
		{
			j = 0;
			cmpa = cmpa->next;
		}
	}
}
