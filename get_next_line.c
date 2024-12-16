/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:23:37 by yimizare          #+#    #+#             */
/*   Updated: 2024/01/18 12:21:25 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char) c)
		s++;
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}

static char	*readingbs(int fd, char *tokeep)
{
	char	*tempbuff;
	int		size;

	size = 1;
	if (BUFFER_SIZE >= SIZE_MAX)
		return (NULL);
	tempbuff = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!tempbuff)
		return (free(tokeep), NULL);
	while (size && !ft_strchr(tokeep, '\n'))
	{
		size = read(fd, tempbuff, BUFFER_SIZE);
		if (size < 0)
		{
			free(tempbuff);
			free(tokeep);
			return (NULL);
		}
		tempbuff[size] = '\0';
		tokeep = ft_strjoin(tokeep, tempbuff);
	}
	free(tempbuff);
	return (tokeep);
}

static char	*readline(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!s || s[i] == '\0')
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] && s[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, s, i + 1);
	return (line);
}

static char	*resttokeep(char *s)
{
	char	*left;
	int		i;
	int		length;

	i = 0;
	if (!s || !s[i])
		return (NULL);
	while (s[i] != '\n' && s[i])
		i++;
	if (!s[i])
		return (NULL);
	length = ((ft_strlen(s) - i) + 1);
	left = malloc(length * sizeof(char));
	if (!left)
		return (NULL);
	else
		ft_strlcpy(left, s + i + 1, length);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*tokeep;
	char		*tempofall;
	char		*tobereturned;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	tempofall = readingbs(fd, tokeep);
	tobereturned = readline(tempofall);
	tokeep = resttokeep(tempofall);
	free(tempofall);
	return (tobereturned);
}
