/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:48:10 by ussef             #+#    #+#             */
/*   Updated: 2023/10/25 02:13:12 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  check_path(char *path)
{
int i;

i = 0;
while(path[i])
	i++;
if(path[--i] == '/')
	return(1);
return(0);
}

char *find_path(char **paths, char *cmd)
{
	int i;
	char *line;

	i = 0;
	line = NULL;
	while(paths[++i])
		{	
			if(check_path(paths[i]))
			{
				line = ft_strjoin(paths[i], cmd);
				if(!access(line, F_OK)) 
					return(line);
				free(line);
			}
			else
			{
			line = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
				if(!access(line, F_OK)) 
					return(line);
				free(line);
			}
		}
	return(NULL);
}

char **get_paths(t_env *env, char *s)
{
	char **paths;

	while(env)
	{
		if(!ft_strncmp(env->name, s, INT_MAX))
		{
			paths = ft_split(env->data , ':');
			return (paths);
		}
		env = env->next;
	}
	return (NULL);
}

void	ft_err(t_cmd *command)
{
	write(2, "bash: ", 6);
	write(2, command->cmd[0], ft_strlen(command->cmd[0]));
	write(2, ": command not found\n", 20);
}