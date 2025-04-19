/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils05.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:36:49 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 02:40:07 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_opened(char *str)
{
	int	fd;

	if (is_directory(str))
		return (0);
	fd = open(str, O_RDONLY, 0777);
	if (fd == -1)
		return (0);
	else
		close(fd);
	return (1);
}

int	is_textures_accesible(t_map *map)
{
	short	i;

	if (!map->textures[0]->name || !map->textures[1]->name
		|| !map->textures[2]->name || !map->textures[3]->name)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (!is_opened(map->textures[i]->name))
			return (0);
		i++;
	}
	return (1);
}

int	check_colors(t_map *map)
{
	if (map->ceiling_color == -1 || map->floor_color == -1)
		return (0);
	return (1);
}

int	get_max_width(t_map *map)
{
	int	i;
	int	length;
	int	max_width;

	i = 0;
	max_width = 0;
	if (!map->grid[0])
		return (0);
	while (map->grid[i])
	{
		length = ft_strlen(map->grid[i]);
		if (length > max_width)
			max_width = length;
		i++;
	}
	map->map_width = max_width;
	return (max_width);
}

void	free_grid(char **grid, int height)
{
	int	y;

	y = 0;
	if (!grid)
		return ;
	while (y < height)
	{
		if (grid[y])
			free(grid[y]);
		y++;
	}
	free(grid);
}
