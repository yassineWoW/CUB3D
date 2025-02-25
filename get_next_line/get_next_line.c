#include <stdio.h>
#include "get_next_line.h"

char	*prepare_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	line = malloc (i + 1);
	if (!line | !buff[0])
		return (free(line), NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		line[i] = buff[i];
		i++;
	}
	return (line[i] = '\0', line);
}

static char	*read_data(int fd, char *buff, char *str)
{
	int	n;

	n = 1;
	while (!(ft_strchr2(str, '\n')) && n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
		{
			free(buff);
			if (str)
				free(str);
			return (NULL);
		}
		buff[n] = '\0';
		str = ft_strjoin2(str, buff);
	}
	return (str);
}

static char	*getdata(int fd, char *str)
{
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	str = read_data(fd, buff, str);
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = getdata(fd, buff);
	if (!buff)
		return (NULL);
	line = prepare_line(buff);
	buff = save_next_line(buff);
	return (line);
}
