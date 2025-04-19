/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:17:35 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 03:17:36 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	clean_images_doors(t_mlxing *mlx, int j)
{
	printf("Error: Failed to load door texture.\n");
	while (++j < mlx->shoot_animation->frame_count)
	{
		if (mlx->shoot_animation->frames[j].img)
			mlx_destroy_image(mlx->mlx_connect,
				mlx->shoot_animation->frames[j].img);
	}
	if (mlx->shoot_animation->frames)
	{
		free(mlx->shoot_animation->frames);
		mlx->shoot_animation->frames = NULL;
	}
	if (mlx->shoot_animation)
	{
		free(mlx->shoot_animation);
		mlx->shoot_animation = NULL;
	}
	if (mlx->initial_img && mlx->initial_img->img)
	{
		mlx_destroy_image(mlx->mlx_connect, mlx->initial_img->img);
		free(mlx->initial_img);
	}
}

void	destroy_mlx_in_doors(t_mlxing *mlx)
{
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
	if (mlx->map->doors)
	{
		free(mlx->map->doors);
		mlx->map->doors = NULL;
	}
	if (mlx->door_texture)
	{
		free(mlx->door_texture);
		mlx->door_texture = NULL;
	}
}

void	my_mlx_error(void)
{
	write(2, "problem with mlx memory allocation\n", 35);
	exit(1);
}

void	door_xpm_fail(t_mlxing *mlx, int i, int j)
{
	clean_images_doors(mlx, j);
	while (i < 4)
	{
		if (mlx->map->textures[i])
		{
			if (mlx->map->textures[i]->image)
			{
				if (mlx->map->textures[i]->image->img)
					mlx_destroy_image(mlx->mlx_connect,
						mlx->map->textures[i]->image->img);
			}
		}
		i++;
	}
	destroy_mlx_in_doors(mlx);
	free_parsing_of_exit(mlx, 0);
	ft_malloc(0, 1);
	exit(1);
}
