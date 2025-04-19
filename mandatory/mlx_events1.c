/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:37:07 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/14 21:37:09 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_player_position(t_mlxing *mlx, double move_speed,
		double *new_center_x, double *new_center_y)
{
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	handle_movement(mlx, move_speed, &dx, &dy);
	normalize_movement(&dx, &dy, move_speed);
	if (dx != 0 || dy != 0)
	{
		*new_center_x += dx;
		*new_center_y += dy;
		mlx->moved = 1;
	}
	return (mlx->moved);
}

int	key_press(int key, t_mlxing *mlx)
{
	if (key == XK_Escape)
		return (exit_game(mlx, 1));
	if (key == XK_w)
		mlx->keys->w_pressed = 1;
	else if (key == XK_s)
		mlx->keys->s_pressed = 1;
	else if (key == XK_a)
		mlx->keys->a_pressed = 1;
	else if (key == XK_d)
		mlx->keys->d_pressed = 1;
	else if (key == XK_Left)
		mlx->keys->left_pressed = 1;
	else if (key == XK_Right)
		mlx->keys->right_pressed = 1;
	return (0);
}

int	key_release(int key, t_mlxing *mlx)
{
	if (key == XK_w)
		mlx->keys->w_pressed = 0;
	else if (key == XK_s)
		mlx->keys->s_pressed = 0;
	else if (key == XK_a)
		mlx->keys->a_pressed = 0;
	else if (key == XK_d)
		mlx->keys->d_pressed = 0;
	else if (key == XK_Left)
		mlx->keys->left_pressed = 0;
	else if (key == XK_Right)
		mlx->keys->right_pressed = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_mlxing *mlx)
{
	static int	last_mouse_x = -1;
	int			delta_x;

	(void)y;
	if (last_mouse_x == -1)
		last_mouse_x = x;
	delta_x = x - last_mouse_x;
	mlx->map->player->angle += delta_x * MOUSE_SENSITIVITY;
	if (mlx->map->player->angle < 0)
		mlx->map->player->angle += 2 * M_PI;
	if (mlx->map->player->angle > 2 * M_PI)
		mlx->map->player->angle -= 2 * M_PI;
	last_mouse_x = x;
	mlx->needs_redraw = 1;
	return (0);
}
