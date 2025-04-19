/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:58 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 03:18:59 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_door	*find_door_at(t_map *map, int map_x, int map_y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].x == map_x && map->doors[i].y == map_y)
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}

void	calculate_hit_distances(t_mlxing *mlx, t_ray *ray,
		double *horizontal_dist, double *vertical_dist)
{
	*horizontal_dist = horizontal_inter(mlx, ray);
	*vertical_dist = vertical_inter(mlx, ray);
	if (*horizontal_dist < *vertical_dist)
	{
		ray->wall_hit_x = ray->h_wall_hit_x;
		ray->wall_hit_y = ray->h_wall_hit_y;
		ray->ray_distance = *horizontal_dist;
		ray->hit_vertical = 0;
	}
	else
	{
		ray->wall_hit_x = ray->v_wall_hit_x;
		ray->wall_hit_y = ray->v_wall_hit_y;
		ray->ray_distance = *vertical_dist;
		ray->hit_vertical = 1;
	}
}

void	handle_door_hit(t_ray *ray)
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	step;

	ray_dir_x = cos(ray->ray_angle);
	ray_dir_y = sin(ray->ray_angle);
	step = 1.0;
	ray->h_wall_hit_x += ray_dir_x * step;
	ray->h_wall_hit_y += ray_dir_y * step;
	ray->v_wall_hit_x += ray_dir_x * step;
	ray->v_wall_hit_y += ray_dir_y * step;
}

int	check_hit_type(t_mlxing *mlx, t_ray *ray, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_y >= mlx->map->map_height
		|| map_x >= mlx->map->map_width)
		return (1);
	if (mlx->map->grid[map_y][map_x] == 'D')
	{
		ray->is_door = 1;
		return (1);
	}
	else if (mlx->map->grid[map_y][map_x] == '1')
	{
		return (1);
	}
	else if (mlx->map->grid[map_y][map_x] == 'd')
	{
		handle_door_hit(ray);
		return (0);
	}
	else
	{
		return (1);
	}
}
