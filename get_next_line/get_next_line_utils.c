#include "get_next_line.h"

char	*ft_strchr2(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	len_str(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *str, char *src)
{
	size_t	i;

	i = 0;
	while (src && src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin2(char *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len = len_str(s1) + len_str(s2);
	str = (char *)malloc(len + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	str[0] = '\0';
	ft_strcpy(str, (char *)s1);
	ft_strcpy((str + len_str(s1)), (char *)s2);
	free(s1);
	return (str);
}

char	*save_next_line(char *buff)
{
	int		i;
	int		i2;
	char	*next_line;

	i = 0;
	i2 = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	next_line = malloc(len_str(buff) - i);
	if (!next_line)
	{
		free(buff);
		return (NULL);
	}
	i++;
	while (buff[i])
		next_line[i2++] = buff[i++];
	next_line[i2] = '\0';
	free(buff);
	return (next_line);
}
