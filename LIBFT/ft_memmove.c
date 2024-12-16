/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:28:35 by yimizare          #+#    #+#             */
/*   Updated: 2023/11/28 20:23:27 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*sbuffer;
	unsigned char	*dbuffer;

	sbuffer = (unsigned char *)src;
	dbuffer = (unsigned char *)dst;
	if (len == 0 || sbuffer == dbuffer)
		return (dst);
	if (dbuffer >= sbuffer + len || sbuffer > dbuffer)
	{
		while (len--)
			*dbuffer++ = *sbuffer++;
	}
	else
	{
		dbuffer += len;
		sbuffer += len;
		while (len > 0)
		{
			*(--dbuffer) = *(--sbuffer);
			len--;
		}
	}
	return (dst);
}
