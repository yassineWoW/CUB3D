/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:37:26 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/14 21:37:27 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_exit_texs(t_mlxing *mlx, int i)
{
	while (i < 4)
	{
		if (mlx->map && mlx->map->textures[i])
		{
			if (mlx->map->textures[i]->image
				&& mlx->map->textures[i]->image->img)
			{
				mlx_destroy_image(mlx->mlx_connect,
					mlx->map->textures[i]->image->img);
				mlx->map->textures[i]->image->img = NULL;
			}
		}
		i++;
	}
}

int	exit_game(t_mlxing *mlx, int iscleanexit)
{
	int	i;

	i = 0;
	if (!mlx)
		return (exit(1), 0);
	clean_exit_texs(mlx, i);
	if (iscleanexit && mlx->image && mlx->image->img)
	{
		mlx_destroy_image(mlx->mlx_connect, mlx->image->img);
		mlx->image->img = NULL;
	}
	if (mlx->mlx_window)
	{
		mlx_destroy_window(mlx->mlx_connect, mlx->mlx_window);
		mlx->mlx_window = NULL;
	}
	if (mlx->mlx_connect)
	{
		mlx_destroy_display(mlx->mlx_connect);
		free(mlx->mlx_connect);
		mlx->mlx_connect = NULL;
	}
	free_parsing(mlx, 0);
	return (exit(0), 0);
}

void	my_mlx_error(void)
{
	write(2, "problem with mlx memory allocation\n", 35);
	exit(1);
}

int	init_mlx(t_mlxing *mlx)
{
	mlx->mlx_connect = mlx_init();
	if (!mlx->mlx_connect)
		return (0);
	mlx->mlx_window = mlx_new_window(mlx->mlx_connect, WINDOW_WIDTH,
			WINDOW_HEIGHT, "CUB3D_3D");
	if (!init_textures(mlx))
	{
		return (0);
	}
	mlx->needs_redraw = 0;
	mlx->moved = 0;
	draw_3d_grid(mlx);
	capture_events(mlx);
	mlx_loop(mlx->mlx_connect);
	return (1);
}
