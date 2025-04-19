/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:36:50 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/14 21:36:51 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*get_current_texture(t_mlxing *mlx, t_ray *ray, t_map *map)
{
	(void)mlx;
	if (ray->hit_vertical)
	{
		if (ray->is_right)
			return (map->textures[2]->image);
		else
			return (map->textures[3]->image);
	}
	else
	{
		if (ray->is_up)
			return (map->textures[0]->image);
		else
			return (map->textures[1]->image);
	}
}

double	calculate_wall_x(t_ray *ray)
{
	double	wall_x;

	if (ray->hit_vertical)
		wall_x = ray->wall_hit_y - floor(ray->wall_hit_y / CELL_SIZE)
			* CELL_SIZE;
	else
		wall_x = ray->wall_hit_x - floor(ray->wall_hit_x / CELL_SIZE)
			* CELL_SIZE;
	wall_x /= CELL_SIZE;
	return (wall_x);
}

double	calculate_wall_strip_height(t_ray *ray, t_mlxing *mlx)
{
	double	wall_strip_height;
	double	projected_distance;
	double	angle_diff;

	angle_diff = ray->ray_angle - mlx->map->player->angle;
	angle_diff = fmod(angle_diff, 2 * M_PI);
	if (angle_diff < 0)
		angle_diff += 2 * M_PI;
	projected_distance = ray->ray_distance * cos(angle_diff);
	wall_strip_height = (CELL_SIZE / projected_distance) * mlx->ppd;
	return (wall_strip_height);
}

void	determine_wall_top_bottom(double wall_strip_height, int *wall_top,
		int *wall_bottom)
{
	*wall_top = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
	*wall_bottom = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
}

t_image	*get_texture(t_mlxing *mlx, t_ray *ray)
{
	return (get_current_texture(mlx, ray, mlx->map));
}
