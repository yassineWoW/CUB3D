/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:29:55 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:53:24 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*remove_char(char *s, char c)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(s);
	while (s[i])
	{
		if (s[i] != c)
		{
			s[j] = tmp[i];
			j++;
		}
		i++;
	}
	free(tmp);
	return (s);
}

int	parse_map(char *str, t_map *map)
{
	if (!check_map_syntax(str))
	{
		return (0);
	}
	copy_old_lines(map, str);
	map->n_rows++;
	return (1);
}

int	is_valid(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int	all_element_founded(t_map *map)
{
	return (map->ceiling_color != -1 && map->floor_color != -1
		&& map->textures[0]->name != NULL && map->textures[1]->name != NULL
		&& map->textures[2]->name != NULL && map->textures[3]->name != NULL);
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
	{
		return (0);
	}
	return (1);
}
