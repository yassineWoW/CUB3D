/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:17:24 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:44:32 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_anim(t_animation *anim, int frame_count)
{
	int	i;

	i = -1;
	anim->frames = malloc(sizeof(t_image) * frame_count);
	if (!anim->frames)
	{
		fprintf(stderr, "Error: Failed to allocate\
		memory for animation frames\n");
		return ;
	}
	anim->frame_count = frame_count;
	anim->current_frame = 0;
	anim->is_playing = 0;
	anim->loop = 0;
	anim->frame_time = 0.1;
	anim->elapsed_time = 0.0;
	while (++i < frame_count)
	{
		anim->frames[i].img = NULL;
	}
}

void	clean_stuff(t_mlxing *mlx, t_animation *anim)
{
	if (mlx->initial_img && mlx->initial_img->img)
	{
		mlx_destroy_image(mlx->mlx_connect, mlx->initial_img->img);
	}
	if (mlx->initial_img)
	{
		free(mlx->initial_img);
		mlx->initial_img = NULL;
	}
	if (anim->frames)
	{
		free(anim->frames);
		anim->frames = NULL;
	}
	if (anim)
	{
		free(anim);
		anim = NULL;
	}
}

void	cleanup_animation(t_mlxing *mlx, t_animation *anim)
{
	int	i;

	i = 0;
	if (!anim)
		return ;
	while (i < anim->frame_count)
	{
		if (anim && &anim->frames[i] && anim->frames[i].img)
		{
			mlx_destroy_image(mlx->mlx_connect, anim->frames[i].img);
			anim->frames[i].img = NULL;
		}
		i++;
	}
	clean_stuff(mlx, anim);
}

void	load_initial_image(t_mlxing *mlx)
{
	mlx->initial_img->img = mlx_xpm_file_to_image(mlx->mlx_connect,
			"sprites/gun_sprite_0/0.xpm", &mlx->initial_img->width,
			&mlx->initial_img->height);
	if (!mlx->initial_img->img)
	{
		fprintf(stderr, "Error: Failed to load initial image\n");
		return ;
	}
	mlx->initial_img->addr = mlx_get_data_addr(mlx->initial_img->img,
			&mlx->initial_img->bpp, &mlx->initial_img->line_length,
			&mlx->initial_img->endian);
}

void	render_initial_image(t_mlxing *mlx, int x, int y)
{
	t_image	*initial_image;

	int (sy), (sx), (pixel_color), (dx), (dy);
	sx = -1;
	sy = -1;
	initial_image = mlx->initial_img;
	while (++sy < initial_image->height)
	{
		sx = -1;
		while (++sx < initial_image->width)
		{
			pixel_color = ((int *)initial_image->addr)[sy * initial_image->width
				+ sx];
			if ((pixel_color & 0xFF000000) == 0xFF000000)
			{
				sx++;
				continue ;
			}
			dx = x + sx;
			dy = y + sy;
			if (dx >= 0 && dx < WINDOW_WIDTH && dy >= 0 && dy < WINDOW_HEIGHT)
				((int *)mlx->image->addr)[dy * WINDOW_WIDTH + dx] = pixel_color;
		}
	}
}
