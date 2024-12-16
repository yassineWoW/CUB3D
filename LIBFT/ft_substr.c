/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:49:25 by yimizare          #+#    #+#             */
/*   Updated: 2023/11/27 15:24:35 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	end;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	end = 0;
	if (len == 0 || start >= slen)
		return (ft_calloc(1, 1));
	if (start < slen)
		end = slen - start;
	if (end > len)
		end = len;
	new = (char *)ft_calloc(end + 1, 1);
	if (!new)
		return (0);
	ft_strlcpy(new, s + start, end + 1);
	return (new);
}
