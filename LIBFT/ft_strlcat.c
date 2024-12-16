/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:06:08 by yimizare          #+#    #+#             */
/*   Updated: 2023/11/29 17:41:22 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t Ndstsize)
{
	size_t	i;
	size_t	j;
	size_t	sl;
	size_t	dl;

	if (dst == NULL && Ndstsize == 0)
		return (ft_strlen(src));
	sl = ft_strlen(src);
	j = ft_strlen(dst);
	dl = j;
	if (Ndstsize == 0 || Ndstsize < dl)
		return (Ndstsize + sl);
	i = 0;
	while (src[i] != '\0' && j + 1 < Ndstsize)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = 0;
	return (sl + dl);
}
