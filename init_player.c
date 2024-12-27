#include "cub3d.h"

void	update_player_grid(int grid_x, int grid_y, int new_center_x, int new_center_y, t_mlxing *mlx)
{
	if (grid_x >= 0 && grid_x < mlx->map->map_width &&
		grid_y >= 0 && grid_y < mlx->map->map_height &&
		mlx->map->grid[grid_y][grid_x] != '1')
	{
		mlx->map->player->center_x = new_center_x;
		mlx->map->player->center_y = new_center_y;
		mlx->map->player->x = grid_x;
		mlx->map->player->y = grid_y;
	}
}

int is_collision(double new_x, double new_y, t_mlxing *mlx)
{
	double collision_buffer = 2.0;
	int num_samples = 6;
	double angle_step = (2 * M_PI) / num_samples;

	for (int i = 0; i < num_samples; i++)
	{
		double angle = i * angle_step;
		double check_x = new_x + cos(angle) * collision_buffer;
		double check_y = new_y + sin(angle) * collision_buffer;

		int grid_x = (int)(check_x / mlx->map->cell_width);
		int grid_y = (int)(check_y / mlx->map->cell_height);

		if (grid_x < 0 || grid_y < 0 || grid_x >= mlx->map->map_width || grid_y >= mlx->map->map_height)
			return 1;
		if (mlx->map->grid[grid_y][grid_x] == '1')
			return 1;
	}

	return 0;
}

int move_player(int key, t_mlxing *mlx)
{
	double move_speed = 5.0;
	double new_center_x = mlx->map->player->center_x;
	double new_center_y = mlx->map->player->center_y;

	if (!mlx || !mlx->map || !mlx->map->player)
	{
		printf("Player structure is not initialized properly.\n");
		return 0;
	}
	if (key == XK_w)
	{
		new_center_x += cos(mlx->map->player->angle) * move_speed;
		new_center_y += sin(mlx->map->player->angle) * move_speed;
	}
	else if (key == XK_s)
	{
		new_center_x -= cos(mlx->map->player->angle) * move_speed;
		new_center_y -= sin(mlx->map->player->angle) * move_speed;
	}
	else if (key == XK_a)
	{
		new_center_x += sin(mlx->map->player->angle) * move_speed;
		new_center_y -= cos(mlx->map->player->angle) * move_speed;
	}
	else if (key == XK_d)
	{
		new_center_x -= sin(mlx->map->player->angle) * move_speed;
		new_center_y += cos(mlx->map->player->angle) * move_speed;
	}
	else
		return 0;

	if (!is_collision(new_center_x, new_center_y, mlx))
	{
		mlx->map->player->center_x = new_center_x;
		mlx->map->player->center_y = new_center_y;
		return 1;
	}
	return 0;
}


int rotate_player(int key, t_map *map)
{
	if (key == XK_Left)
	{
		map->player->angle -= 0.1;
		if (map->player->angle < 0)
			map->player->angle += 2 * PI;
	}
	else if (key == XK_Right)
	{
		map->player->angle += 0.1;
		if (map->player->angle > 2 * PI)
			map->player->angle -= 2 * PI;
	}
	else
		return (0);
	return (1);
}

void init_player(t_mlxing *mlx)
{
	if (!mlx->map->player)
	{
		perror("Failed to allocate memory for player");
		exit(EXIT_FAILURE);
	}
	mlx->map->player->x = mlx->map->map_width / 4;
	mlx->map->player->y = mlx->map->map_height / 4;
	mlx->map->player->angle = 0.0;
	mlx->map->player->radius = 5;
	mlx->map->player->player_direction = 'N';
}

