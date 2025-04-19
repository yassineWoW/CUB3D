/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events4_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:18:36 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 03:18:37 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	start_shoot_animation(t_mlxing *mlx)
{
	mlx->shoot_animation->current_frame = 0;
	mlx->shoot_animation->is_playing = 1;
	mlx->shoot_animation->loop = 0;
}

int	is_player_in_range(t_door *door, int player_x, int player_y, int range)
{
	return (abs(door->x - player_x) <= range && abs(door->y
			- player_y) <= range);
}

void	toggle_door_state(t_door *door, char **grid)
{
	door->is_open = !door->is_open;
	if (door->is_open)
		grid[door->y][door->x] = 'd';
	else
		grid[door->y][door->x] = 'D';
}

void	update_open_door(t_door *door, double animation_speed, char **grid)
{
	if (door->offset < CELL_SIZE)
		door->offset += animation_speed;
	if (door->offset >= CELL_SIZE)
	{
		door->offset = CELL_SIZE;
		grid[door->y][door->x] = 'd';
	}
}

void	update_closed_door(t_door *door, double animation_speed, char **grid)
{
	if (door->offset > 0)
		door->offset -= animation_speed;
	if (door->offset <= 0)
	{
		door->offset = 0;
		grid[door->y][door->x] = 'D';
	}
}
