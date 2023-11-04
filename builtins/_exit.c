/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:28:18 by ybouchra          #+#    #+#             */
/*   Updated: 2023/11/04 08:52:36 by ybouchra         ###   ########.fr       */
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
		write(2, "exit", 4);
		exit(0);
	}
	if (!check_arg(commands->cmd[1]))
	{
		if (!commands->cmd[2])
		{
			write(2, "exit", 4);
			exit(ft_atoi(commands->cmd[1]));
		}
		write(2, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		exit(1);
	}
	write(2, "exit\nminishell: exit: ", 22);
	write(2, commands->cmd[1], ft_strlen(commands->cmd[1]));
	write(2, ": numeric argument required\n", 28);
	exit(255); 
	return (0);
}
