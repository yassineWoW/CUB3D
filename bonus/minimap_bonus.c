/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:07 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:45:53 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calc_s_tile(t_mlxing *mlx)
{
	mlx->s_tile_x = floor(mlx->map->player->center_x / CELL_SIZE)
		- VISIBLE_RANGE;
	mlx->s_tile_y = floor(mlx->map->player->center_y / CELL_SIZE)
		- VISIBLE_RANGE;
}

void	draw_map(t_mlxing *mlx)
{
	int (dy), (dx), (map_x), (map_y);
	calc_s_tile(mlx);
	dy = -1;
	while (++dy <= VISIBLE_RANGE * 2)
	{
		dx = -1;
		while (++dx <= VISIBLE_RANGE * 2)
		{
			map_x = mlx->s_tile_x + dx;
			map_y = mlx->s_tile_y + dy;
			mlx->tile_x = (map_x * CELL_SIZE - mlx->map->player->center_x)
				* MINIMAP_SCALE;
			mlx->tile_y = (map_y * CELL_SIZE - mlx->map->player->center_y)
				* MINIMAP_SCALE;
			if (map_x >= 0 && map_y >= 0 && map_y < mlx->map->map_height
				&& map_x < mlx->map->map_width)
			{
				draw_tile(mlx, map_x, map_y);
			}
		}
	}
}

void	draw_minimap_player(t_mlxing *mlx, int center_x, int center_y)
{
	double	distance;
	double	screen_x;
	double	screen_y;

	int (x), (y);
	y = -PLAYER_RADIUS - 1;
	while (++y <= PLAYER_RADIUS)
	{
		x = -PLAYER_RADIUS - 1;
		while (++x <= PLAYER_RADIUS)
		{
			distance = sqrt(x * x + y * y);
			if (distance <= PLAYER_RADIUS)
			{
				screen_x = center_x + x;
				screen_y = center_y + y;
				if (screen_x >= 0 && screen_x < WINDOW_WIDTH && screen_y >= 0
					&& screen_y < WINDOW_HEIGHT)
				{
					minimap_pixel_put(screen_x, screen_y, mlx->image,
						MINIMAP_COLOR_PLAYER);
				}
			}
		}
	}
}

void	draw_minimap_rays(t_mlxing *mlx, int center_x, int center_y)
{
	int (i), (step);
	double (ray_angle), (end_x), (end_y), (dx), (dy), (steps), (x_inc), (y_inc),
		(x), (y);
	i = -31;
	while (++i <= 30)
	{
		ray_angle = mlx->map->player->angle + (i * FOV / 60);
		end_x = center_x + cos(ray_angle) * RAY_LENGTH;
		end_y = center_y + sin(ray_angle) * RAY_LENGTH;
		dx = end_x - center_x;
		dy = end_y - center_y;
		steps = fmax(fabs(dx), fabs(dy));
		x_inc = dx / steps;
		y_inc = dy / steps;
		x = center_x;
		y = center_y;
		step = -1;
		while (++step <= steps)
		{
			minimap_pixel_put(round(x), round(y), mlx->image,
				MINIMAP_COLOR_RAY);
			x += x_inc;
			y += y_inc;
		}
	}
}

void	draw_minimap(t_mlxing *mlx)
{
	int	outline_color;

	outline_color = BLACK;
	draw_background(mlx->image, CENTER_X, CENTER_Y);
	draw_map(mlx);
	draw_minimap_player(mlx, CENTER_X, CENTER_Y);
	draw_minimap_rays(mlx, CENTER_X, CENTER_Y);
	draw_minimap_outline(mlx->image, CENTER_X, CENTER_Y, outline_color);
}
