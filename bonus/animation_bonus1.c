/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:17:22 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:44:24 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	init_shoot_anim(t_mlxing *mlx)
{
	mlx->initial_img = malloc(sizeof(t_image));
	mlx->initial_img->img = NULL;
	mlx->shoot_animation = malloc(sizeof(t_animation));
	mlx->shoot_animation->frames = NULL;
	mlx->shoot_animation->frame_count = 0;
	mlx->shoot_animation->current_frame = 0;
	mlx->shoot_animation->is_playing = 0;
	mlx->shoot_animation->loop = 0;
	mlx->shoot_animation->frame_time = 0.1;
	mlx->shoot_animation->elapsed_time = 0.0;
	return (0);
}

void	render_animation(t_mlxing *mlx, t_animation *anim, int x, int y)
{
	t_image	*frame;

	int (sy), (sx), (p_c), (dx), (dy);
	if (anim->is_playing == 0)
		render_initial_image(mlx, x, y);
	if (anim->is_playing)
	{
		frame = &anim->frames[anim->current_frame];
		sy = -1;
		while (++sy < frame->height)
		{
			sx = -1;
			while (++sx < frame->width)
			{
				p_c = ((int *)frame->addr)[sy * frame->width + sx];
				if ((p_c & 0xFF000000) != 0xFF000000)
				{
					dx = x + sx;
					dy = y + sy;
					if (bound_check(dx, dy))
						((int *)mlx->image->addr)[dy * WINDOW_WIDTH + dx] = p_c;
				}
			}
		}
	}
}

void	free_textures_from_anim(t_mlxing *mlx, t_animation *anim)
{
	int	i;

	i = 0;
	free(anim->frames);
	anim->frames = NULL;
	mlx_destroy_image(mlx->mlx_connect, mlx->initial_img->img);
	free(mlx->initial_img);
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
}

int	bound_check(int dx, int dy)
{
	return (dx >= 0 && dx < WINDOW_WIDTH && dy >= 0 && dy < WINDOW_HEIGHT);
}
