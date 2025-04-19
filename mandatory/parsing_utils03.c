/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils03.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:36:56 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:33:22 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	iscolor_clean(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_colors(char *str, t_map *map)
{
	if (!str)
		return (0);
	if (!strncmp(str, "F", 1))
	{
		if (map->floor_color != -1)
			return (0);
		map->isfloor_color = 1;
	}
	else if (!strncmp(str, "C", 1))
	{
		if (map->ceiling_color != -1)
			return (0);
		map->isceiling_color = 1;
	}
	if (!iscolor_clean(str))
		return (0);
	str = ft_strtrim(str, "FC ");
	if (!validate_colors_syntax(str))
		return (0);
	if (!set_colorsvalue(str, map))
		return (0);
	return (1);
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
