/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:59:33 by yimizare          #+#    #+#             */
/*   Updated: 2023/11/28 13:54:15 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextnode;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		nextnode = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nextnode;
	}
}
