/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils06.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:40:16 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 02:44:30 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cleanup_doors(t_mlxing *mlx)
{
	if (mlx->door_texture && mlx->door_texture->img)
	{
		mlx_destroy_image(mlx->mlx_connect, mlx->door_texture->img);
	}
	if (mlx->map->doors)
	{
		free(mlx->map->doors);
		mlx->map->doors = NULL;
	}
	if (mlx->door_texture)
	{
		free(mlx->door_texture);
	}
}

int	check_data(t_map *map, t_mlxing *mlx)
{
	char	**padded;

	padded = NULL;
	map->map_height = map->n_rows;
	map->map_width = get_max_width(map);
	if (!is_one_player(map))
		return (0);
	if (!is_map_closed(map))
		return (0);
	if (!is_textures_accesible(map))
		return (0);
	if (!check_colors(map))
	{
		return (0);
	}
	padded = pad_map_grid(map->grid, map->map_height, map->map_width);
	if (!padded)
	{
		free_grid(map->grid, map->map_height);
		return (0);
	}
	free_grid(map->grid, map->map_height);
	map->grid = padded;
	init_doors(mlx);
	return (1);
}

void	set_player_angle(t_player *player, char direction)
{
	if (direction == 'N')
		player->angle = -M_PI / 2;
	else if (direction == 'S')
		player->angle = M_PI / 2;
	else if (direction == 'W')
		player->angle = M_PI;
	else if (direction == 'E')
		player->angle = 0.0;
}

void	exit_with_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	init_player(t_mlxing *mlx)
{
	int	y;
	int	x;

	if (!mlx->map->player)
		exit_with_error("Failed to allocate memory for player");
	y = -1;
	while (++y < mlx->map->map_height)
	{
		x = -1;
		while (++x < mlx->map->map_width)
		{
			if (mlx->map->grid[y][x] == 'N' || mlx->map->grid[y][x] == 'S'
				|| mlx->map->grid[y][x] == 'W' || mlx->map->grid[y][x] == 'E')
			{
				mlx->map->player->x = x + 0.5;
				mlx->map->player->y = y + 0.5;
				set_player_angle(mlx->map->player, mlx->map->grid[y][x]);
				mlx->map->grid[y][x] = '0';
				return ;
			}
		}
	}
	exit_with_error("");
}
