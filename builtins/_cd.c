/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:01:18 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/06 22:11:41 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_home_dir(t_env *env, char *target)
{
	char *home;
	if(!env)
		return(NULL);
	while(env)
	{
		if(!ft_strncmp(env->name, target, ft_strlen(target)))
		{
			home = ft_strdup(env->data);
			return(home);
		}
		env = env->next;
	}
	return (NULL);
}
void msg_err(t_cmd *command)
{
	write(2, "minishell: cd :", 16);
	write(2, command->cmd[1], ft_strlen(command->cmd[1]));
	write(2, ": No such file or directory\n", 29);
	g_exit_status = 1;
}

void	set_env(t_env **env, char *old, char *new)
{
	t_env *container;

	container = *env;
	while(container)
	{
		if(!ft_strncmp(container->name, "PWD", INT_MAX))
			container->data = ft_strdup(new);
		if(!ft_strncmp(container->name, "OLDPWD", INT_MAX))
			container->data = ft_strdup(old);
		container = container->next;		
	}
}

int _cd(t_cmd *command, t_env *env)
{
	char *home_dir;
	char *old_pwd;
	char *new_pwd = NULL;

	
	home_dir = get_home_dir(env, "HOME");
	old_pwd = getcwd(NULL, 0);
	
	if(!command->cmd[1] || (command->cmd[1][0] == '~' && !command->cmd[1][1]))
	{
		chdir(home_dir); 
		new_pwd = getcwd(NULL, 0);
		set_env(&env, old_pwd, new_pwd);
	}
	else if(!chdir(command->cmd[1]))
	{
		new_pwd = getcwd(NULL, 0);
		set_env(&env, old_pwd, new_pwd);
	}
	else 
	{
		free(old_pwd);
		free(home_dir);
		free(new_pwd);
		old_pwd = NULL;
		new_pwd = NULL;
		new_pwd = NULL;
		msg_err(command);
	}

	return 0;
}