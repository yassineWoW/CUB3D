/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:27:01 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 02:28:53 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	count_char(char *s, char c)
{
	int	count_c;

	count_c = 0;
	while (*s)
	{
		if (*s == c)
			count_c++;
		s++;
	}
	return (count_c);
}

int	count_word(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_map_line(char *str)
{
	int		i;
	short	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0')
			counter++;
		if (counter >= 1)
			return (1);
		i++;
	}
	return (0);
}

int	copy_old_lines(t_map *map, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!str || !map)
		return (0);
	tmp = malloc((map->n_rows + 2) * sizeof(char *));
	while (map->grid[i])
	{
		tmp[i] = map->grid[i];
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	free(map->grid);
	map->grid = tmp;
	return (1);
}

int	check_map_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] == '0' || str[i] == '1') || (str[i] == 'S'
					|| str[i] == 'N' || str[i] == 'W' || str[i] == 'E')
				|| (str[i] == 32) || str[i] == 'D'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
