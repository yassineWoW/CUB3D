#include "cub3d_bonus.h"

void	load_initial_image(t_mlxing *mlx)
{
	mlx->initial_img->img = mlx_xpm_file_to_image(mlx->mlx_connect,
			"sprites/gun_sprite_0/0.xpm",
			&mlx->initial_img->width, &mlx->initial_img->height);
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
			pixel_color = ((int *)initial_image->addr)[sy
				* initial_image->width + sx];
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

int	bound_check(int dx, int dy)
{
	return (dx >= 0 && dx < WINDOW_WIDTH && dy >= 0 && dy < WINDOW_HEIGHT);
}

void	init_anim(t_animation *anim, int frame_count)
{
	anim->frames = malloc(sizeof(t_image) * frame_count);
	if (!anim->frames)
	{
		fprintf(stderr, "Error: Failed to allocate \
		memory for animation frames\n");
		return ;
	}
	anim->frame_count = frame_count;
	anim->current_frame = 0;
	anim->is_playing = 0;
	anim->loop = 0;
	anim->frame_time = 0.1;
	anim->elapsed_time = 0.0;
}

void	load_animation(t_mlxing *mlx, t_animation *anim,
		const char *folder, int frame_count)
{
	char	path[256];

	int (i), (j);
	i = -1;
	init_anim(anim, frame_count);
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
			free(anim->frames);
			anim->frames = NULL;
			return ;
		}
		anim->frames[i].addr = mlx_get_data_addr(anim->frames[i].img,
				&anim->frames[i].bpp, &anim->frames[i].line_length,
				&anim->frames[i].endian);
	}
}
