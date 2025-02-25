#include "cub3d_bonus.h"

void	calculate_horizontal_step(t_ray *ray, t_mlxing *mlx)
{
	mlx->h_y_step = CELL_SIZE;
	mlx->h_x_step = CELL_SIZE / tan(ray->ray_angle);
	if (ray->is_up)
		mlx->h_y_step *= -1;
	if ((ray->is_left && mlx->h_x_step > 0)
		|| (ray->is_right && mlx->h_x_step < 0))
		mlx->h_x_step *= -1;
}

void	initialize_horizontal_intercept(t_mlxing *mlx, t_ray *ray)
{
	mlx->h_y_intercept = floor(mlx->map->player->center_y / CELL_SIZE)
		* CELL_SIZE;
	if (ray->is_down)
		mlx->h_y_intercept += CELL_SIZE;
	else if (ray->is_up)
		mlx->h_y_intercept -= 0.0001;
	mlx->h_x_intercept = mlx->map->player->center_x
		+ (mlx->h_y_intercept - mlx->map->player->center_y)
		/ tan(ray->ray_angle);
}

float	find_horizontal_hit(t_mlxing *mlx, t_ray *ray)
{
	int		i;
	float	horizontal_h_d;

	i = 0;
	horizontal_h_d = 0;
	while (mlx->h_next_x_touch >= 0 && mlx->h_next_x_touch
		<= mlx->map->map_width * CELL_SIZE
		&& mlx->h_next_y_touch >= 0 && mlx->h_next_y_touch
		<= mlx->map->map_height * CELL_SIZE
		&& i < mlx->h_max_iterations)
	{
		if (check_wall_collision(mlx, mlx->h_next_y_touch, mlx->h_next_x_touch))
		{
			ray->h_wall_hit_x = mlx->h_next_x_touch;
			ray->h_wall_hit_y = mlx->h_next_y_touch;
			horizontal_h_d = calculate_distance(mlx->map->player->center_x,
					mlx->map->player->center_y, ray->h_wall_hit_x,
					ray->h_wall_hit_y);
			break ;
		}
		mlx->h_next_x_touch += mlx->h_x_step;
		mlx->h_next_y_touch += mlx->h_y_step;
		i++;
	}
	return (horizontal_h_d);
}

float	horizontal_inter(t_mlxing *mlx, t_ray *ray)
{
	float	horizontal_hit_distance;

	calculate_horizontal_step(ray, mlx);
	initialize_horizontal_intercept(mlx, ray);
	mlx->h_next_x_touch = mlx->h_x_intercept;
	mlx->h_next_y_touch = mlx->h_y_intercept;
	mlx->h_max_iterations = 1000;
	horizontal_hit_distance = find_horizontal_hit(mlx, ray);
	if (horizontal_hit_distance == 0)
		return (1e30);
	return (horizontal_hit_distance);
}
