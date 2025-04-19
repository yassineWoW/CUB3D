/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:38:08 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:41:26 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_player(void *param)
{
	t_mlxing	*mlx;

	mlx = (t_mlxing *)param;
	double (move_speed), (rotate_speed), (new_center_x), (new_center_y);
	move_speed = 2.0;
	rotate_speed = 0.03;
	new_center_x = mlx->map->player->center_x;
	new_center_y = mlx->map->player->center_y;
	mlx->moved = handle_rotation(mlx, rotate_speed);
	mlx->moved = update_player_position(mlx, move_speed, &new_center_x,
			&new_center_y);
	handle_player_movement(mlx, new_center_x, new_center_y);
	handle_redraw(mlx);
	return (0);
}

void	capture_events(t_mlxing *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, &key_press, mlx);
	mlx_hook(mlx->mlx_window, KeyRelease, KeyReleaseMask, &key_release, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, StructureNotifyMask, &exit_game,
		mlx);
	mlx_loop_hook(mlx->mlx_connect, &update_player, mlx);
}
