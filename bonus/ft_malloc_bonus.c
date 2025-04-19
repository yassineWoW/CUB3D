/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:17:44 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 03:17:45 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_lstclear(t_leaks **lst)
{
	t_leaks	*current;
	t_leaks	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (current->ptr)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	*ft_malloc(int size, int flag)
{
	static t_leaks	*address;
	void			*p;
	t_leaks			*new_node;

	p = NULL;
	if (flag)
	{
		free_lstclear(&address);
		return (NULL);
	}
	p = malloc(size);
	if (!p)
		return (NULL);
	new_node = malloc(sizeof(t_leaks));
	if (!new_node)
	{
		free(p);
		return (NULL);
	}
	new_node->ptr = p;
	new_node->next = address;
	address = new_node;
	return (p);
}
