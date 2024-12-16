#include "cub3d.h"

int key_press(int key, t_mlxing *mlx)
{
	
	if (key == XK_Escape)
		return (exit_game(mlx));
	else
	{
		if (move_player(key, mlx) || rotate_player(key, mlx->map))
			redraw_3d_grid(mlx);
	return (0);
	}
}

void	capture_events(t_mlxing *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, &key_press, mlx);
}