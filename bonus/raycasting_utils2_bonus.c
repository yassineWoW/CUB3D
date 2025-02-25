#include "cub3d_bonus.h"

void	initialize_vertical_intercept(t_mlxing *mlx, t_ray *ray)
{
	mlx->v_x_intercept = floor(mlx->map->player->center_x / CELL_SIZE)
		* CELL_SIZE;
	if (ray->is_right)
		mlx->v_x_intercept += CELL_SIZE;
	else if (ray->is_left)
		mlx->v_x_intercept -= 0.0001;
	mlx->v_y_intercept = mlx->map->player->center_y
		+ (mlx->v_x_intercept - mlx->map->player->center_x)
		* tan(ray->ray_angle);
}

void	calculate_vertical_step(t_ray *ray, t_mlxing *mlx)
{
	mlx->v_x_step = CELL_SIZE;
	mlx->v_y_step = tan(ray->ray_angle) * CELL_SIZE;
	if (ray->is_left)
		mlx->v_x_step *= -1;
	if (ray->is_up && mlx->v_y_step > 0)
		mlx->v_y_step *= -1;
	if (ray->is_down && mlx->v_y_step < 0)
		mlx->v_y_step *= -1;
}

float	find_vertical_hit(t_mlxing *mlx, t_ray *ray)
{
	int		i;
	float	vertical_h_d;

	i = 0;
	vertical_h_d = 0;
	while (mlx->v_next_x_touch >= 0 && mlx->v_next_x_touch
		<= mlx->map->map_width * CELL_SIZE
		&& mlx->v_next_y_touch >= 0 && mlx->v_next_y_touch
		<= mlx->map->map_height * CELL_SIZE
		&& i < mlx->v_max_iterations)
	{
		if (check_wall_collision(mlx, mlx->v_next_y_touch, mlx->v_next_x_touch))
		{
			ray->v_wall_hit_x = mlx->v_next_x_touch;
			ray->v_wall_hit_y = mlx->v_next_y_touch;
			vertical_h_d = calculate_distance(mlx->map->player->center_x,
					mlx->map->player->center_y, ray->v_wall_hit_x,
					ray->v_wall_hit_y);
			break ;
		}
		mlx->v_next_x_touch += mlx->v_x_step;
		mlx->v_next_y_touch += mlx->v_y_step;
		i++;
	}
	return (vertical_h_d);
}

float	vertical_inter(t_mlxing *mlx, t_ray *ray)
{
	float	vertical_hit_distance;

	calculate_vertical_step(ray, mlx);
	initialize_vertical_intercept(mlx, ray);
	mlx->v_next_x_touch = mlx->v_x_intercept;
	mlx->v_next_y_touch = mlx->v_y_intercept;
	mlx->v_max_iterations = 1000;
	vertical_hit_distance = find_vertical_hit(mlx, ray);
	if (vertical_hit_distance == 0)
		return (1e30);
	return (vertical_hit_distance);
}
