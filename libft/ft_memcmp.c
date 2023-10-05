/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 00:55:13 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/01/15 09:14:46 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*p1;

	p1 = (unsigned char *)s1;
	p = (unsigned char *)s2;
	i = 0;
	while (n > i)
	{
		if (p1[i] != p[i])
			return (p1[i] - p[i]);
		i++;
	}
	return (0);
}
