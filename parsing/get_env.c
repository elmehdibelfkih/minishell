/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:25:45 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/10 18:38:01 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_get_env(char **envp)
{
	t_env	*head_env;
	char	**spl;
	int		i;

	i = 0;
	head_env = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		spl = ft_split(envp[i], '=');
		ft_env_add_back(&head_env,
			ft_envnew(ft_strdup(spl[0]), ft_strdup(spl[1])));
		ft_clear(spl, INT_MAX);
		i++;
	}
	return (head_env);
}

t_env	*ft_envnew(char *name, char *data)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->name = name;
	new->data = data;
	new->next = NULL;
	return (new);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*p;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		if (!(*lst))
			new->next = NULL;
		if (!new)
			return ;
		new->next = *lst;
		*lst = new;
	}
	else
	{
		p = ft_envlast(*lst);
		p->next = new;
	}
}

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_envclear(t_env **lst)
{
	t_env	*t;

	t = *lst;
	if (!*lst)
		return ;
	while (*lst)
	{
		free((*lst)->name);
		free((*lst)->data);
		t = (*lst)->next;
		free(*lst);
		*lst = t;
	}
}
