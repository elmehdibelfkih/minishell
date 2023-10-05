/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:03:59 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/01/15 09:40:50 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*s1;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	j = 0;
	if (i < start)
		return (ft_calloc(1, 1));
	else if (i >= start + len)
		s1 = malloc(len + 1);
	else
		s1 = malloc(i - start + 1);
	if (!s1)
		return (NULL);
	while (len-- > 0 && s[start])
		s1[j++] = s[start++];
	s1[j] = '\0';
	return (s1);
}
