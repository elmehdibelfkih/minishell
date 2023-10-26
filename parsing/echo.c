/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:21:57 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/26 00:23:10 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_start(char **cmd, bool *s)
{
	int	i;
	int	j;

	i = 1;
	*s = true;
	if (!cmd[1])
		return (1);
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j])
		{
			if (i != 1)
				*s = false;
			return (i);
		}
		i++;
	}
	if (i != 1)
		*s = false;
	return (i);
}

void	echo(char **cmd, int fd)
{
	int		i;
	int		j;
	bool	s;

	if (!cmd)
		return ;
	i = echo_start(cmd, &s);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			write(fd, &cmd[i][j], 1);
			j++;
		}
		if (cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (s)
		write(fd, "\n", 1);
}
