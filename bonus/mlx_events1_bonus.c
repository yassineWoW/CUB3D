/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:29 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/18 15:38:06 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_wall_or_closed_door(char cell)
{
	return (cell == '1' || cell == 'D');
}

double	calculate_distance2(double x1, double y1, double x2, double y2)
{
	double	dist_x;
	double	dist_y;

	dist_x = x2 - x1;
	dist_y = y2 - y1;
	return (sqrt(dist_x * dist_x + dist_y * dist_y));
}

void	adjust_p_p(t_player *player, double wall_x, double wall_y,
		double buffer_distance)
{
	double (dist_x), (dist_y), (dist_to_wall), (push_x), (push_y);
	dist_x = wall_x - player->center_x;
	dist_y = wall_y - player->center_y;
	dist_to_wall = calculate_distance2(player->center_x, player->center_y,
			wall_x, wall_y);
	if (dist_to_wall < buffer_distance)
	{
		push_x = dist_x / dist_to_wall * (buffer_distance - dist_to_wall);
		push_y = dist_y / dist_to_wall * (buffer_distance - dist_to_wall);
		player->center_x -= push_x;
		player->center_y -= push_y;
	}
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
	else if (key == XK_space)
		start_shoot_animation(mlx);
	else if (key == XK_e)
	{
		mlx->keys->e_pressed = 1;
		handle_door_interaction(mlx);
	}
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
	else if (key == XK_e)
		mlx->keys->e_pressed = 0;
	return (0);
}
