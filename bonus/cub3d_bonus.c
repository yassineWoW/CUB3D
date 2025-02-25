#include "cub3d_bonus.h"

void	init_player_map(t_mlxing *mlx, char *file)
{
	parse_cub(file, mlx);
	init_player(mlx);
}

t_mlxing	*init_mlx_structure(void)
{
	t_mlxing	*mlx;

	mlx = (t_mlxing *)malloc(sizeof(t_mlxing));
	if (!mlx)
		return (NULL);
	if (init_shoot_anim(mlx))
		return (NULL);
	mlx->map = (t_map *)malloc(sizeof(t_map));
	if (!mlx->map)
		return (free(mlx), NULL);
	mlx->image = (t_image *)malloc(sizeof(t_image));
	if (!mlx->image)
		return (free(mlx->map), free(mlx), NULL);
	mlx->map->player = (t_player *)malloc(sizeof(t_player));
	if (!mlx->map->player)
		return (free(mlx->image), free(mlx->map), free(mlx), NULL);
	mlx->keys = (t_keys *)malloc(sizeof(t_keys));
	if (!mlx->keys)
		return (free(mlx->map->player), free(mlx->image),
			free(mlx->map), free(mlx), NULL);
	return (mlx);
}

static void	cleanup_mlx_structure(t_mlxing *mlx)
{
	if (mlx->keys)
		free(mlx->keys);
	if (mlx->map->player)
		free(mlx->map->player);
	if (mlx->image)
		free(mlx->image);
	if (mlx->map)
		free(mlx->map);
	if (mlx)
		free(mlx);
}

int	main(int ac, char **av)
{
	t_mlxing	*mlx;

	if (ac != 2)
	{
		perror("Usage: ./cub3D <path_to_map.cub>");
		return (1);
	}
	mlx = init_mlx_structure();
	if (!mlx)
	{
		perror("Failed to initialize mlx structure");
		return (1);
	}
	keyinit(mlx->keys);
	init_player_map(mlx, av[1]);
	init_mlx(mlx);
	cleanup_mlx_structure(mlx);
	return (0);
}
