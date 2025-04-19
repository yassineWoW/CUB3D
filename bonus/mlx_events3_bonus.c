/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:33 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/18 16:01:34 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	clamp_player_position(t_mlxing *mlx)
{
	double	buffer_distance;

	int (player_x), (player_y), (x), (y);
	buffer_distance = 10.0;
	player_x = (int)(mlx->map->player->center_x / CELL_SIZE);
	player_y = (int)(mlx->map->player->center_y / CELL_SIZE);
	y = player_y - 1;
	while (y <= player_y + 1)
	{
		x = player_x - 1;
		while (x <= player_x + 1)
		{
			if (x >= 0 && y >= 0 && y < mlx->map->map_height
				&& x < mlx->map->map_width
				&& is_wall_or_closed_door(mlx->map->grid[y][x]))
			{
				adjust_p_p(mlx->map->player, x * CELL_SIZE + CELL_SIZE / 2, y
					* CELL_SIZE + CELL_SIZE / 2, buffer_distance);
			}
			x++;
		}
		y++;
	}
}

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

void	handle_door_interaction(t_mlxing *mlx)
{
	int		player_x;
	int		player_y;
	int		interaction_range;
	int		i;
	t_door	*door;

	player_x = (int)(mlx->map->player->center_x / CELL_SIZE);
	player_y = (int)(mlx->map->player->center_y / CELL_SIZE);
	interaction_range = 3;
	i = -1;
	while (++i < mlx->map->door_count)
	{
		door = &mlx->map->doors[i];
		if (is_player_in_range(door, player_x, player_y, interaction_range))
		{
			toggle_door_state(door, mlx->map->grid);
			break ;
		}
	}
}

void	update_animation(t_mlxing *mlx, t_animation *anim, double delta_time)
{
	if (!anim->is_playing)
		return ;
	anim->elapsed_time += delta_time;
	if (anim->elapsed_time >= anim->frame_time)
	{
		anim->current_frame++;
		anim->elapsed_time = 0.0;
		if (anim->current_frame >= anim->frame_count)
		{
			if (anim->loop)
				anim->current_frame = 0;
			else
				anim->is_playing = 0;
		}
	}
	mlx->moved = 1;
}
