/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:35:23 by yimizare          #+#    #+#             */
/*   Updated: 2024/01/17 16:13:15 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dupped;

	i = ft_strlen(s1);
	dupped = (char *)malloc(sizeof(char) * (i + 1));
	if (!dupped)
		return (NULL);
	ft_strlcpy(dupped, s1, i + 1);
	dupped[i] = '\0';
	return (dupped);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	if (destsize != 0)
	{
		while (src[i] != '\0' && i < destsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*jointstr;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	jointstr = malloc(len * sizeof(char));
	if (!jointstr)
		return (NULL);
	jointstr[0] = '\0';
	ft_strlcat(jointstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(jointstr, s2, len);
	free(s1);
	return (jointstr);
}

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
