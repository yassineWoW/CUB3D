/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:51 by yimizare          #+#    #+#             */
/*   Updated: 2023/12/01 16:23:50 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mapped;
	size_t			length;

	if (!s || !f)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	mapped = ft_calloc(length + 1, 1);
	if (!mapped)
		return (NULL);
	while (s[i] != '\0')
	{
		mapped[i] = f(i, s[i]);
		i++;
	}
	return (mapped);
}
