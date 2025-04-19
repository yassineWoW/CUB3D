/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:40:02 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/18 21:58:00 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_rgb_toint(t_colors rgb)
{
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

int	set_colors(t_map *map, t_colors color)
{
	if (map->isfloor_color)
	{
		if (map->floor_color != -1)
			return (0);
		map->floor_color = convert_rgb_toint(color);
		map->isfloor_color = 0;
	}
	else if (map->isceiling_color)
	{
		if (map->ceiling_color != -1)
			return (0);
		map->ceiling_color = convert_rgb_toint(color);
		map->isceiling_color = 0;
	}
	return (1);
}

int	set_colorsvalue(char *str, t_map *map)
{
	char		**s;
	t_colors	color;

	s = ft_split(str, ',');
	if (count_word(s) != 3 || count_char(str, ',') != 2)
	{
		free_dbl_arr(s);
		return (0);
	}
	if (!fill_rgb(s, &color))
	{
		free_dbl_arr(s);
		return (0);
	}
	if (!set_colors(map, color))
	{
		free_dbl_arr(s);
		return (0);
	}
	return (1);
}
