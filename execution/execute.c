/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:32:35 by ybouchra          #+#    #+#             */
/*   Updated: 2023/10/06 03:07:34 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


// void	display_cmds(t_cmd *cmd)
// {

// 	printf("--------------------------------------------------------\n");
// 	while (cmd)
// 	{
// 		printf("args: \n\t");
// 		t_list	*lst;
// 		lst = cmd->args;
// 		while (lst)
// 		{
// 			printf("%s ", lst->content);
// 			lst = lst->next;
// 		}
// 		printf("\nredirections: \n");
// 		t_redir *redir;
// 		redir = cmd->redir;
// 		char	*type[] = {"INP", "OUT", "HER", "APP"};
// 		while (redir)
// 		{
// 			printf("\ttype : %s\n\t", type[redir->type - 5]);
// 			printf("file : %s\n", redir->file);
// 			redir = redir->next;
// 		}
// 		cmd = cmd->next;
// 		printf("-------\n");
// 	}
// 	printf("--------------------------------------------------------\n");
// }

// char **get_path(t_env *env,char *s)
// {
// 	char **pp;

// 	while(env)
// 	{
// 		if(!ft_strcmp(env->name, s))
// 		{
// 			pp = ft_split(env->data , ':');
// 			return (pp);
// 		}
// 		env = env->next;
// 	}
// 	return (NULL);
// }
// int get_len(t_cmd *cmd)
// {
// 	int len = 0;
// 	t_list *lst = cmd->args;
// 	while(lst)
// 	{
// 		len++;
// 		lst = lst->next;
// 	}
// 	return(len);
// }

// void insert_cmds(t_cmd *command)
// {
// 	int len = get_len(command);
// 	t_list *lst = command->args;
// 	command->cmd = malloc(sizeof(char*) * (len + 1));
// 	if(!command->cmd)
// 		return;
// 	int i = 0;
// 	while(lst)
// 	{
// 		command->cmd[i++] = ft_strdup(lst->content);
// 		lst = lst->next;
// 	}
// 	command->cmd[i] = NULL;
	
// 	}

// int ft_exec_cmd(char **path, char **args)
// {
// 		int i;
// 		char *line;
// 		pid_t pid;
		
// 		line = NULL;
// 		pid = fork();
// 		if(pid == -1)
// 			return(0);
// 		i = -1;
// 		if(pid == 0)
// 		{
// 			while(path[++i])
// 			{	
// 				line = ft_strjoin(ft_strjoin(path[i], "/"), *args);
// 				if(!access(line, F_OK)) 
// 				{
// 					if(!execve(line, args, NULL))
// 						free(line);
// 				}
// 				free(line);
// 			}
// 		return(write(1,"0_No such file or directory\n", 26), exit(0), 0);
// 		}
// 		else
// 		{
// 			wait(0);
// 		}
// 	return(1);
// }

// void	execute(t_cmd **commands, t_env **env)
// {
// 	char	**paths;
// 	display_cmds(*commands);

// 	insert_cmds(*commands);
// 	paths = get_path(*env, "PATH");
// 	if(!paths)
// 		write(1,"1_No such file or directory\n", 26);
		
// 	if(!ft_exec_cmd(paths, (*commands)->cmd))
// 	{
// 		write(1,"2_No such file or directory\n", 26);
// 		exit(0);
// 	}
	
// }