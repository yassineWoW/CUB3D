#include "cub3d.h"

int	exit_game(t_mlxing *mlx)
{
	if (!mlx)
		return (exit(0), 0);
	if (mlx->mlx_window)
		mlx_destroy_window(mlx->mlx_connect, mlx->mlx_window);
	if (mlx->mlx_connect)
	{
		mlx_destroy_display(mlx->mlx_connect);
		free(mlx->mlx_connect);
	}
	return (exit(0), 0);
}

void	my_mlx_error(void)
{
	write(2, "problem with mlx memory allocation\n", 35);
	exit(1);
}

void	init_mlx(t_mlxing *mlx)
{
	t_ray *rays;

	mlx->mlx_connect = mlx_init();
	if (!mlx->mlx_connect)
		my_mlx_error();
	mlx->mlx_window = mlx_new_window(mlx->mlx_connect, window_WIDTH, window_HEIGHT, "CUB3D_3D");
	rays = malloc(sizeof(t_ray) * NUM_RAYS);
	mlx->rays = rays;
	draw_3d_grid(mlx);
	capture_events(mlx);
	mlx_loop(mlx->mlx_connect);
}
