/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:31 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 03:18:32 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	handle_rotation(t_mlxing *mlx, double rotate_speed)
{
	if (mlx->keys->left_pressed)
	{
		mlx->map->player->angle -= rotate_speed;
		if (mlx->map->player->angle < 0)
			mlx->map->player->angle += 2 * M_PI;
		mlx->moved = 1;
	}
	if (mlx->keys->right_pressed)
	{
		mlx->map->player->angle += rotate_speed;
		if (mlx->map->player->angle > 2 * M_PI)
			mlx->map->player->angle -= 2 * M_PI;
		mlx->moved = 1;
	}
	return (mlx->moved);
}

void	handle_movement(t_mlxing *mlx, double move_speed, double *dx,
		double *dy)
{
	if (mlx->keys->w_pressed)
	{
		*dx += cos(mlx->map->player->angle) * move_speed;
		*dy += sin(mlx->map->player->angle) * move_speed;
	}
	if (mlx->keys->s_pressed)
	{
		*dx -= cos(mlx->map->player->angle) * move_speed;
		*dy -= sin(mlx->map->player->angle) * move_speed;
	}
	if (mlx->keys->a_pressed)
	{
		*dx += sin(mlx->map->player->angle) * move_speed;
		*dy -= cos(mlx->map->player->angle) * move_speed;
	}
	if (mlx->keys->d_pressed)
	{
		*dx -= sin(mlx->map->player->angle) * move_speed;
		*dy += cos(mlx->map->player->angle) * move_speed;
	}
}

void	normalize_movement(double *dx, double *dy, double move_speed)
{
	double	length;

	if (*dx != 0 && *dy != 0)
	{
		length = sqrt(*dx * *dx + *dy * *dy);
		*dx = (*dx / length) * move_speed;
		*dy = (*dy / length) * move_speed;
	}
}

void	handle_player_movement(t_mlxing *mlx, double new_center_x,
		double new_center_y)
{
	if (mlx->moved)
	{
		is_collision(new_center_x, new_center_y, mlx);
		mlx->needs_redraw = 1;
	}
}

void	handle_redraw(t_mlxing *mlx)
{
	if (mlx->needs_redraw)
	{
		redraw_3d_grid(mlx);
		mlx->needs_redraw = 0;
	}
}
