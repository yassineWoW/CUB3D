#include "cub3d_bonus.h"

void start_shoot_animation(t_mlxing *mlx)
{
	printf("Starting shoot animation\n");
	mlx->shoot_animation->current_frame = 0;
	mlx->shoot_animation->is_playing = 1;
	mlx->shoot_animation->loop = 0;
	printf("is_playing: %d\n", mlx->shoot_animation->is_playing);
}

void update_animation(t_animation *anim, double delta_time)
{
	if (!anim->is_playing)
		return;
	anim->elapsed_time += delta_time;
	if (anim->elapsed_time >= anim->frame_time) {
		anim->current_frame++;
		anim->elapsed_time = 0.0;

		if (anim->current_frame >= anim->frame_count) {
			if (anim->loop)
				anim->current_frame = 0;
			else
				anim->is_playing = 0;
		}
	}
}

int	update_player(void *param)
{
	t_mlxing	*mlx;

	mlx = (t_mlxing *)param;
	double (move_speed), (rotate_speed), (new_center_x),
		(new_center_y);
	double delta_time = 0.016;
    update_animation(mlx->shoot_animation, delta_time);
	move_speed = 2.0;
	rotate_speed = 0.03;
	new_center_x = mlx->map->player->center_x;
	new_center_y = mlx->map->player->center_y;
	mlx->moved = handle_rotation(mlx, rotate_speed);
	mlx->moved = update_player_position(mlx, move_speed,
			&new_center_x, &new_center_y);
	handle_player_movement(mlx, new_center_x, new_center_y);
	handle_redraw(mlx);
	return (0);
}

void	capture_events(t_mlxing *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask,
		&key_press, mlx);
	mlx_hook(mlx->mlx_window, KeyRelease, KeyReleaseMask,
		&key_release, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, StructureNotifyMask,
		&exit_game, mlx);
	mlx_hook(mlx->mlx_window, MotionNotify, PointerMotionMask,
		&handle_mouse_move, mlx);
	mlx_mouse_hide(mlx->mlx_connect, mlx->mlx_window);
	mlx_mouse_move(mlx->mlx_connect, mlx->mlx_window,
		WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_loop_hook(mlx->mlx_connect, &update_player, mlx);
}
