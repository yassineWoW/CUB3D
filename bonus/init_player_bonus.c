#include "cub3d_bonus.h"

void	calculate_move_direction(t_mlxing *mlx, double *move_direction_x,
			double *move_direction_y)
{
	double	move_distance;

	*move_direction_x = mlx->new_x - mlx->current_x;
	*move_direction_y = mlx->new_y - mlx->current_y;
	move_distance = sqrt(*move_direction_x * *move_direction_x
			+ *move_direction_y * *move_direction_y);
	if (move_distance > 0)
	{
		*move_direction_x /= move_distance;
		*move_direction_y /= move_distance;
	}
}

int	check_collision_at_angle( double angle, t_mlxing *mlx)
{
	double (buffer), (check_x), (check_y),
		(to_wall_x), (to_wall_y), (dot_product);
	buffer = 0.10;
	check_x = mlx->new_x + cos(angle) * buffer;
	check_y = mlx->new_y + sin(angle) * buffer;
	if (check_wall_collision2(check_x, check_y, mlx))
	{
		to_wall_x = check_x - mlx->current_x;
		to_wall_y = check_y - mlx->current_y;
		dot_product = to_wall_x * mlx->move_direction_x
			+ to_wall_y * mlx->move_direction_y;
		if (dot_product < 0)
			return (0);
		return (1);
	}
	return (0);
}

int	check_collision(t_mlxing *mlx)
{
	int				i;
	const double	angles[8] = {
		0.0, M_PI_4, M_PI_2, 3 * M_PI_4,
		M_PI, 5 * M_PI_4, 3 * M_PI_2, 7 * M_PI_4
	};

	i = -1;
	while (++i < 8)
	{
		if (check_collision_at_angle(angles[i], mlx))
			return (1);
	}
	return (0);
}

int	try_sliding(t_mlxing *mlx)
{
	if (!check_wall_collision2(mlx->new_x, mlx->current_y, mlx))
	{
		mlx->map->player->center_x = mlx->new_x;
		return (1);
	}
	if (!check_wall_collision2(mlx->current_x, mlx->new_y, mlx))
	{
		mlx->map->player->center_y = mlx->new_y;
		return (1);
	}
	return (0);
}

int	is_collision(double new_x, double new_y, t_mlxing *mlx)
{
	int		collision;

	mlx->new_x = new_x;
	mlx->new_y = new_y;
	mlx->current_x = mlx->map->player->center_x;
	mlx->current_y = mlx->map->player->center_y;
	calculate_move_direction(mlx, &mlx->move_direction_x,
		&mlx->move_direction_y);
	collision = check_collision(mlx);
	if (collision)
		return (try_sliding(mlx));
	mlx->map->player->center_x = mlx->new_x;
	mlx->map->player->center_y = mlx->new_y;
	return (0);
}
