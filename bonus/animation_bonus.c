/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:17:18 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:44:17 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_existing_frames(t_mlxing *mlx, t_animation *anim)
{
	int	i;

	i = 0;
	if (anim->frames)
	{
		while (i < anim->frame_count)
		{
			if (anim->frames[i].img)
				mlx_destroy_image(mlx->mlx_connect, anim->frames[i].img);
			i++;
		}
		free(anim->frames);
	}
}

void	init_anim_data(t_animation *anim, int frame_count)
{
	anim->frame_count = frame_count;
	anim->current_frame = 0;
	anim->is_playing = 0;
	anim->loop = 0;
	anim->frame_time = 0.1;
	anim->elapsed_time = 0.0;
}

void	free_mlx(t_mlxing *mlx)
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
	free(mlx->map->doors);
	free_parsing1(mlx, 0);
	ft_malloc(0, 1);
	exit(1);
}

void	allocate_anim(int frame_count, t_animation *anim)
{
	anim->frames = malloc(sizeof(t_image) * frame_count);
	if (!anim->frames)
	{
		fprintf(stderr, "Error: Failed to allocate \
		memory for animation frames\n");
		return ;
	}
}

void	load_animation(t_mlxing *mlx, t_animation *anim, const char *folder,
		int frame_count)
{
	char	path[256];

	int (i), (j);
	i = -1;
	free_existing_frames(mlx, anim);
	allocate_anim(frame_count, anim);
	init_anim_data(anim, frame_count);
	while (++i < frame_count)
	{
		j = -1;
		snprintf(path, sizeof(path), "%s/%d.xpm", folder, i);
		anim->frames[i].img = mlx_xpm_file_to_image(mlx->mlx_connect, path,
				&anim->frames[i].width, &anim->frames[i].height);
		if (!anim->frames[i].img)
		{
			fprintf(stderr, "Error: Failed to load animation frame %s\n", path);
			while (++j < i)
				mlx_destroy_image(mlx->mlx_connect, anim->frames[j].img);
			free_textures_from_anim(mlx, anim);
			free_mlx(mlx);
		}
		anim->frames[i].addr = mlx_get_data_addr(anim->frames[i].img,
				&anim->frames[i].bpp, &anim->frames[i].line_length,
				&anim->frames[i].endian);
	}
}
