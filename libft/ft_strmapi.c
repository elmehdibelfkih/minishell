/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 00:31:57 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/01/15 09:34:10 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s2;
	int		i;

	i = -1;
	if (!s || !f)
		return (NULL);
	s2 = malloc(ft_strlen(s) + 1);
	if (!s2)
		return (NULL);
	while (s[++i])
		s2[i] = f(i, s[i]);
	s2[i] = '\0';
	return (s2);
}
