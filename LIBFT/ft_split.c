/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:00:55 by yimizare          #+#    #+#             */
/*   Updated: 2025/02/18 19:23:02 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**freestr(char	**split, int i)
{
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}

static int	ft_countwords(char const *s, char delimiter)
{
	int	i;
	int	wordcount;
	int	flag;

	i = 0;
	wordcount = 0;
	flag = 1;
	while (s[i] != '\0')
	{
		if (s[i] == delimiter)
			flag = 1;
		if (s[i] != delimiter && flag)
		{
			flag = 0;
			wordcount++;
		}
		i++;
	}
	return (wordcount);
}

static	char	**allowords(char **split, char const *s, int wordcount, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (wordcount > k)
	{
		while (s[i] == c)
			i++;
		j = i;
		if (s[i] != '\0' && s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			split[k] = ft_substr(s, j, i - j);
			if (!split[k])
				return (freestr(split, k));
			k++;
			j = i;
		}
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	int		count;

	if (s == NULL)
		return (NULL);
	count = ft_countwords(s, c);
	splited = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!splited)
		return (NULL);
	if (allowords(splited, s, count, c) == NULL)
		return (NULL);
	return (splited);
}
