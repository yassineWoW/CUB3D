/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:24 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/18 15:44:53 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_doors(t_mlxing *mlx)
{
	double	animation_speed;
	t_door	*door;
	int		i;

	animation_speed = 2.0;
	i = -1;
	while (++i < mlx->map->door_count)
	{
		door = &mlx->map->doors[i];
		if (door->is_open)
			update_open_door(door, animation_speed, mlx->map->grid);
		else
			update_closed_door(door, animation_speed, mlx->map->grid);
	}
	mlx->moved = 1;
}

int	update_player(void *param)
{
	t_mlxing	*mlx;

	double (move_speed), (rotate_speed), (new_center_x), (new_center_y),
		(delta_time);
	mlx = (t_mlxing *)param;
	move_speed = 3.0;
	rotate_speed = 0.03;
	new_center_x = mlx->map->player->center_x;
	new_center_y = mlx->map->player->center_y;
	delta_time = 0.016;
	update_doors(mlx);
	update_animation(mlx, mlx->shoot_animation, delta_time);
	mlx->moved = handle_rotation(mlx, rotate_speed);
	mlx->moved = update_player_position(mlx, move_speed, &new_center_x,
			&new_center_y);
	handle_player_movement(mlx, new_center_x, new_center_y);
	clamp_player_position(mlx);
	handle_redraw(mlx);
	mlx->moved = 0;
	return (0);
}

void	capture_events(t_mlxing *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, &key_press, mlx);
	mlx_hook(mlx->mlx_window, KeyRelease, KeyReleaseMask, &key_release, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, StructureNotifyMask, &exit_game,
		mlx);
	mlx_hook(mlx->mlx_window, MotionNotify, PointerMotionMask,
		&handle_mouse_move, mlx);
	mlx_mouse_move(mlx->mlx_connect, mlx->mlx_window, WINDOW_WIDTH / 2,
		WINDOW_HEIGHT / 2);
	mlx_loop_hook(mlx->mlx_connect, &update_player, mlx);
}
