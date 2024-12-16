#include "cub3d.h"

int main(int ac, char **av)
{
    (void)av;
    (void)ac;
	t_mlxing *mlx;

	mlx = (t_mlxing *)malloc(sizeof(t_mlxing));
	if (!mlx) 
	{
        perror("Failed to allocate mlx");
        return 1;
    }
	mlx->map = (t_map *)malloc(sizeof(t_map));
	if (!mlx->map)
	{
        perror("Failed to allocate map");
        free(mlx);
        return 1;
    }
	mlx->map->player = (t_player *)malloc(sizeof(t_player));
    if (!mlx->map->player) 
	{
        perror("Failed to allocate player");
        free(mlx->map);
        free(mlx);
        return 1;
    }
	init_map_details(mlx);
	init_player(mlx);
	init_mlx(mlx);
    return 0;
}