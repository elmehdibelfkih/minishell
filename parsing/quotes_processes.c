/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 05:32:03 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/14 09:17:56 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_exp_var(char *line, t_env *env)
{
    int i;
    int start;
    char *ex;

    i = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            start = i;
            while (line[i] && line[i] != ' ' &&  line[i] != '\"' && line[i] != '\'')
                i++;
            ex = ft_substr(line, start + 1, i - start - 1);
            return (get_env_var(ex, env));
        }
        i++;
    }
    return ("");
}

char    *get_env_var(char *var, t_env *env)
{
    while (env)
    {
        if (ft_strlen(env->name) == ft_strlen(var)
                && !ft_strncmp(env->name, var, ft_strlen(var)))
        {
            free(var);
            return(env->data);
        }
        env = env->next;
    }
    return ("");
}


char    *replace_var(char *line, t_env *env)
{
    int     i;
    char    *c;
    char    *r;
    char    *f;
    
    c = get_exp_var(line, env);
    i = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            r = ft_substr(line, 0, i);
            f = ft_strjoin(r, c);
            free (r);
            while (line[i] && line[i] != ' ' &&  line[i] != '\"' && line[i] != '\'')
                i++;
            r = ft_strjoin(f, &line[i]);
            free (f);
            return (r);
        }
        i++;
    }
    return (NULL);
}

void	replace_line(t_comp *cmpa, t_env *env)
{
    char *tmp;

	while (cmpa)
	{
		if (cmpa->tok != delimiter && cmpa->expanded)
		{
			tmp = replace_var(cmpa->data, env);
            free(cmpa->data);
            cmpa->data = tmp;
            if (!ft_strchr(tmp, '$'))
                cmpa->expanded = false;
		}
		else
			cmpa = cmpa->next;
	}
}