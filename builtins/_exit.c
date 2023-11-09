/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:28:18 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/09 15:43:32 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arg(char *arg)
{
	int	i;

	i = -1;
	if (arg[0] == '-' && arg[1])
		i++;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
	}
	return (0);
}

int	__exit(t_cmd *commands)
{
	int	i;

	i = 0;
	if (commands->cmd[1] == NULL)
	{
		write(2, "exit", 5);
		exit(0);
	}
	if (!check_arg(commands->cmd[1]))
	{
		if (!commands->cmd[2])
		{
			write(2, "exit", 4);
			exit(ft_atoi(commands->cmd[1]));
		}
		write(2, "exit\n", 6);
		write(2, "minishell: exit: too many arguments\n", 37);
		exit(1);
	}
	write(2, "exit\n", 6);
	write(2, "minishell: exit: ", 18);
	write(2, commands->cmd[1], ft_strlen(commands->cmd[1]));
	write(2, ": numeric argument required\n", 29);
	exit(255); 
	return (0);
}
