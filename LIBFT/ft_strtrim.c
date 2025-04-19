/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mouk <oel-mouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:29:57 by yimizare          #+#    #+#             */
/*   Updated: 2025/02/28 17:28:41 by oel-mouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_str(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s && s[i])
		i++;
	return (i);
}

char	*ft_strtrim(char *s1, char const *set)
{
	int		start;
	int		end;
	char	*trimed_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = len_str(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (s1);
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	trimed_str = (char *)malloc(end - start + 2);
	if (!trimed_str)
		return (NULL);
	ft_strlcpy(trimed_str, &s1[start], end - start + 2);
	ft_strlcpy(s1, trimed_str, strlen(s1));
	free(trimed_str);
	return (s1);
}
