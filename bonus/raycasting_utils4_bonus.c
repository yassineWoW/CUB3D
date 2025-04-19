/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils4_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:55 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:49:43 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cast_ray(t_mlxing *mlx, t_ray *ray)
{
	double	horizontal_dist;
	double	vertical_dist;

	int (map_x), (map_y), (loop_count), (max_loops);
	max_loops = 10;
	ray->is_door = 0;
	loop_count = 0;
	while (loop_count < max_loops)
	{
		loop_count++;
		calculate_hit_distances(mlx, ray, &horizontal_dist, &vertical_dist);
		map_x = (int)(ray->wall_hit_x / CELL_SIZE);
		map_y = (int)(ray->wall_hit_y / CELL_SIZE);
		if (check_hit_type(mlx, ray, map_x, map_y))
			break ;
	}
	if (ray->ray_distance > MAX_RENDER_DISTANCE)
		ray->ray_distance = MAX_RENDER_DISTANCE;
	ray->wall_stripe_height = (CELL_SIZE / ray->ray_distance) * mlx->ppd;
}

void	init_ray(t_ray *ray)
{
	ray->is_down = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->is_up = !ray->is_down;
	ray->is_right = ray->ray_angle < (M_PI / 2) || ray->ray_angle > M_PI * 1.5;
	ray->is_left = !ray->is_right;
	ray->hit_horizontal = 0;
	ray->hit_vertical = 0;
	ray->h_wall_hit_x = 0;
	ray->h_wall_hit_y = 0;
	ray->v_wall_hit_x = 0;
	ray->v_wall_hit_y = 0;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->ray_distance = 0;
	ray->wall_stripe_height = 0;
	ray->is_door = 0;
}

void	cast_all_rays(t_mlxing *mlx)
{
	t_ray	*ray;
	double	ray_angle;
	int		i;

	i = 0;
	ray_angle = mlx->map->player->angle - (FOV / 2);
	while (i < WINDOW_WIDTH)
	{
		ray = &mlx->rays[i];
		ray->ray_angle = normalize_angle(ray_angle);
		init_ray(ray);
		cast_ray(mlx, ray);
		ray_angle += FOV / WINDOW_WIDTH;
		i++;
	}
}
