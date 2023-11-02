/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:29:02 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/01 07:16:29 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	n_of_world(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*s == '\0')
		return (0);
	if (s[i] != c)
		j++;
	while (s[++i])
		if (s[i] != c && s[i - 1] == c)
			j++;
	return (j);
}

int	ft_clear(char **spl, int p)
{
	int	i;

	i = 0;
	if (!spl)
		return (-1);
	while (i < p && spl[i])
		free(spl[i++]);
	free(spl);
	return (-1);
}

int	plen(char **spl, const char *s, char c)
{
	int			i;
	size_t		p;
	size_t		len;
	int			start;

	i = -1;
	len = 0;
	p = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i++] != c && s[i - 1])
				len++;
			spl[p++] = ft_substr(s, start, len);
			if (spl[p - 1] == NULL)
				return (ft_clear(spl, p));
			len = 0;
			i -= 2;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**spl;

	if (!s)
		return (NULL);
	spl = malloc((n_of_world(s, c) + 1) * sizeof(char *));
	if (!spl)
		return (NULL);
	spl[n_of_world(s, c)] = NULL;
	if (plen(spl, s, c) < 0)
		return (NULL);
	return (spl);
}
