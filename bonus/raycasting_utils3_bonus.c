#include "cub3d_bonus.h"

void	cast_ray(t_mlxing *mlx, t_ray *ray)
{
	double	horizontal_grid_distance;
	double	vertical_grid_distance;

	horizontal_grid_distance = horizontal_inter(mlx, ray);
	vertical_grid_distance = vertical_inter(mlx, ray);
	if (horizontal_grid_distance < vertical_grid_distance)
	{
		ray->wall_hit_x = ray->h_wall_hit_x;
		ray->wall_hit_y = ray->h_wall_hit_y;
		ray->ray_distance = horizontal_grid_distance;
		ray->hit_horizontal = 1;
	}
	else
	{
		ray->wall_hit_x = ray->v_wall_hit_x;
		ray->wall_hit_y = ray->v_wall_hit_y;
		ray->ray_distance = vertical_grid_distance;
		ray->hit_vertical = 1;
	}
	ray->ray_distance *= cos(ray->ray_angle - mlx->map->player->angle);
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
}

void	cast_all_rays(t_mlxing *mlx)
{
	t_ray	*ray;
	double	ray_angle;
	int		i;

	i = 0;
	ray_angle = mlx->map->player->angle - (FOV / 2);
	while (i < NUM_RAYS)
	{
		ray = &mlx->rays[i];
		ray->ray_angle = normalize_angle(ray_angle);
		init_ray(ray);
		cast_ray(mlx, ray);
		ray_angle += FOV / NUM_RAYS;
		i++;
	}
}
