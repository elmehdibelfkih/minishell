/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:03:56 by ybouchra          #+#    #+#             */
/*   Updated: 2023/10/28 17:17:17 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    save_fd(t_exec_info *exec_info)
{
	exec_info->def_inp = dup(0);
	exec_info->def_out = dup(1);
}
char	**list_to_tab(t_env *env)
{
        int		len;
        t_env	*tmp;
        char	*name;
        char	**arr;

        tmp = env;
        len = 0;
        while (env){
            len++;
            env = env->next;
        }
        arr = malloc(sizeof(char *) * len + 1);
        if (!arr)
            return (NULL);
        len = -1;
        env = tmp;
        while (env){
            name = ft_strjoin(env->name, "=");
            arr[++len] = ft_strjoin(name, env->data);
            free(name);
            env = env->next;
        }
        arr[++len] = NULL;
        return (arr);
}


void reset_fd( t_exec_info *exec_info)
{
	(dup2(exec_info->def_out, 1), dup2(exec_info->def_inp, 0));
	(close(exec_info->def_out), close(exec_info->def_inp));
}

void		handle_sigint(int sig)
{	
	(void)sig;
	// printf("%d\n", sig);
	if(sig == SIGINT)
	{
		printf("\nCTR + C\n");
		exit(0);
	}	

}

void    handle_sigQ(int sig)
{	
	(void)sig;
	printf("%d\n", sig);
	if(sig == SIGQUIT)
		printf("\n CTR + /\n");
}