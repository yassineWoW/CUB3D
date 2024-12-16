/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:03:45 by yimizare          #+#    #+#             */
/*   Updated: 2023/11/30 20:58:44 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dupped;

	i = ft_strlen(s1);
	dupped = (char *)malloc(sizeof(char) * (i + 1));
	if (dupped == NULL)
		return (0);
	ft_strlcpy(dupped, s1, i + 1);
	dupped[i] = '\0';
	return (dupped);
}
