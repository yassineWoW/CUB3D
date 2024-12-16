/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:08:14 by yimizare          #+#    #+#             */
/*   Updated: 2023/12/01 16:31:07 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*headnode;
	t_list	*newnode;

	headnode = NULL;
	if (!lst)
		return (NULL);
	if (f && del)
	{
		while (lst)
		{
			newnode = ft_lstnew(f(lst->content));
			if (!newnode)
			{
				ft_lstclear(&headnode, del);
				return (NULL);
			}
			ft_lstadd_back(&headnode, newnode);
			lst = lst->next;
		}
	}
	return (headnode);
}
