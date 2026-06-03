/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:39:52 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/23 18:56:37 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*newnode;

	if (!lst)
		return (NULL);
	newl = NULL;
	while (lst != NULL)
	{
		if (f)
			newnode = ft_lstnew(f(lst->content));
		else
			newnode = ft_lstnew(lst->content);
		if (!newnode)
		{
			ft_lstclear(&newl, del);
			return (NULL);
		}
		ft_lstadd_back (&newl, newnode);
		lst = lst->next;
	}
	return (newl);
}
