/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils08.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:56:15 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/18 21:13:00 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	locate_door(int x, int y, t_mlxing *mlx)
{
	int	door_index;

	door_index = 0;
	while (y < mlx->map->map_height)
	{
		x = 0;
		while (x < mlx->map->map_width)
		{
			if (mlx->map->grid[y][x] == 'D')
			{
				mlx->map->doors[door_index].x = x;
				mlx->map->doors[door_index].y = y;
				mlx->map->doors[door_index].is_open = 0;
				mlx->map->doors[door_index].offset = 0;
				door_index++;
			}
			x++;
		}
		y++;
	}
}

void	init_doors(t_mlxing *mlx)
{
	int (y), (x), (door_index);
	y = 0;
	x = 0;
	(void)door_index;
	mlx->map->door_count = 0;
	while (y < mlx->map->map_height)
	{
		x = 0;
		while (x < mlx->map->map_width)
		{
			if (mlx->map->grid[y][x] == 'D')
				mlx->map->door_count++;
			x++;
		}
		y++;
	}
	mlx->map->doors = malloc(sizeof(t_door) * mlx->map->door_count);
	if (!mlx->map->doors)
		exit(1);
	door_index = 0;
	y = 0;
	x = 0;
	locate_door(x, y, mlx);
}

char	**pad_map_grid(char **grid, int map_height, int map_width)
{
	char	**padded_grid;
	int		x;
	int		y;
	int		line_width;

	x = 0;
	y = 0;
	padded_grid = malloc((map_height + 1) * sizeof(char *));
	if (!padded_grid)
		exit(EXIT_FAILURE);
	while (y < map_height)
	{
		padded_grid[y] = malloc((map_width + 1) * sizeof(char));
		if (!padded_grid[y])
			exit(EXIT_FAILURE);
		line_width = ft_strlen(grid[y]);
		ft_strcpy(padded_grid[y], grid[y]);
		x = line_width;
		while (x++ < map_width)
			padded_grid[y][x] = '1';
		padded_grid[y][map_width] = '\0';
		y++;
	}
	padded_grid[y] = NULL;
	return (padded_grid);
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

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		return (0);
	}
	return (S_ISDIR(path_stat.st_mode));
}
