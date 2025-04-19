/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:19:04 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 03:19:06 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_pixel_put(int x, int y, t_image *image, int color)
{
	int	pixel_index;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
	{
		return ;
	}
	pixel_index = (y * image->line_length) + (x * (image->bpp / 8));
	*(unsigned int *)(image->addr + pixel_index) = color;
}

void	clear_image(t_image *image, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			my_pixel_put(x, y, image, color);
		}
	}
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	double	distance;

	distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (distance);
}

int	check_wall_collision(t_mlxing *mlx, double next_y_touch,
		double next_x_touch)
{
	int	app_map_x;
	int	app_map_y;

	app_map_x = (int)(next_x_touch / CELL_SIZE);
	app_map_y = (int)(next_y_touch / CELL_SIZE);
	if (next_x_touch < 0 || next_y_touch < 0)
		return (1);
	if (app_map_y >= mlx->map->map_height || app_map_x >= mlx->map->map_width)
		return (1);
	return (mlx->map->grid[app_map_y][app_map_x] == '1'
		|| mlx->map->grid[app_map_y][app_map_x] == 'D');
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
