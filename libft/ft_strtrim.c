/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:34:36 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/24 00:11:01 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_first(char const *s1, char const *set)
{
	int	i;

	i = -1;
	while (s1[++i])
		if (!ft_strchr(set, s1[i]))
			return (i);
	return (-1);
}

int	ft_is_last(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (s1[--i])
		if (!ft_strchr(set, s1[i]))
			return (i);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	if (ft_is_first(s1, set) == -1)
		return (ft_strdup(""));
	return (ft_substr(s1, ft_is_first(s1, set),
			ft_is_last(s1, set) - ft_is_first(s1, set) + 1));
}
