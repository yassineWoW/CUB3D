/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:38 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:47:16 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	clean_images(t_mlxing *mlx, int iscleanexit)
{
	if (iscleanexit && mlx->image && mlx->image->img)
	{
		mlx_destroy_image(mlx->mlx_connect, mlx->image->img);
		mlx->image->img = NULL;
	}
	cleanup_animation(mlx, mlx->shoot_animation);
	cleanup_doors(mlx);
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
}

int	exit_game(t_mlxing *mlx, int iscleanexit)
{
	int	i;

	i = 0;
	if (!mlx)
		return (exit(1), 0);
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
	clean_images(mlx, iscleanexit);
	free_parsing_of_exit(mlx, 0);
	return (exit(0), 0);
}

void	load_door_texture(t_mlxing *mlx)
{
	int (width), (height), (j), (i);
	j = -1;
	i = 0;
	width = 0;
	height = 0;
	mlx->door_texture = malloc(sizeof(t_image));
	if (!mlx->door_texture)
	{
		printf("Error: Failed to allocate memory for door texture.\n");
		door_xpm_fail(mlx, i, j);
	}
	mlx->door_texture->img = mlx_xpm_file_to_image(mlx->mlx_connect,
			"textures/doors/door.xpm", &width, &height);
	if (!mlx->door_texture->img)
		door_xpm_fail(mlx, i, j);
	mlx->door_texture->width = width;
	mlx->door_texture->height = height;
	mlx->door_texture->addr = mlx_get_data_addr(mlx->door_texture->img,
			&mlx->door_texture->bpp, &mlx->door_texture->line_length,
			&mlx->door_texture->endian);
}

int	init_mlx(t_mlxing *mlx)
{
	t_ray	*rays;

	mlx->mlx_connect = mlx_init();
	if (!mlx->mlx_connect)
		my_mlx_error();
	mlx->mlx_window = mlx_new_window(mlx->mlx_connect, WINDOW_WIDTH,
			WINDOW_HEIGHT, "CUB3D_3D");
	if (!init_textures(mlx))
	{
		return (0);
	}
	rays = ft_malloc(sizeof(t_ray) * WINDOW_WIDTH, 0);
	mlx->rays = rays;
	mlx->needs_redraw = 0;
	mlx->moved = 0;
	load_initial_image(mlx);
	load_animation(mlx, mlx->shoot_animation, "./sprites/gun_sprite_0", 22);
	load_door_texture(mlx);
	draw_3d_grid(mlx);
	capture_events(mlx);
	mlx_loop(mlx->mlx_connect);
	return (1);
}
