#include "cub3d_bonus.h"

int	init_shoot_anim(t_mlxing *mlx)
{
	mlx->initial_img = (t_image *)malloc(sizeof(t_image));
	if (!mlx->initial_img)
		return (free(mlx), 1);
	mlx->shoot_animation = (t_animation *)malloc(sizeof(t_animation));
	if (!mlx->shoot_animation)
		return (free(mlx->initial_img), free(mlx), 1);
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
