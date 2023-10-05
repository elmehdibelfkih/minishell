/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:41:53 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/01/15 09:18:50 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ks(int n)
{
	if (n == 0)
		return ("0");
	if (n == -2147483648)
		return ("-2147483648");
	return (NULL);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	num;

	if (ks(n))
		return (ft_putstr_fd(ks(n), fd));
	num = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = -n;
	}
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
		ft_putchar_fd(num + 48, fd);
}
