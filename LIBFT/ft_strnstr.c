/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:07:29 by yimizare          #+#    #+#             */
/*   Updated: 2023/12/01 15:52:46 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *kawma, const char *ibra, size_t len)
{
	size_t	i;
	size_t	ibra_len;
	size_t	j;

	i = 0;
	if (!kawma && !len && ibra)
		return (NULL);
	ibra_len = ft_strlen(ibra);
	if (!*ibra)
		return ((char *)kawma);
	while (kawma[i] && i < len)
	{
		if (kawma[i] == *ibra)
		{
			j = 0;
			while (kawma[i + j] == ibra[j] && i + j < len)
			{
				if (j == ibra_len - 1)
					return ((char *)&kawma[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
