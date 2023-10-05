/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:37:56 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/01/15 09:10:48 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*h;

	if (!lst || !f || !del)
		return (NULL);
	r = ft_lstnew(f(lst->content));
	if (!r)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		h = ft_lstnew(f(lst->content));
		ft_lstadd_back(&r, h);
		if (!h)
		{
			ft_lstclear(&r, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (r);
}
