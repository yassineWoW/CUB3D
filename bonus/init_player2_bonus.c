/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:17:58 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 03:17:59 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	keyinit(t_keys *keys)
{
	keys->w_pressed = 0;
	keys->s_pressed = 0;
	keys->a_pressed = 0;
	keys->d_pressed = 0;
	keys->left_pressed = 0;
	keys->right_pressed = 0;
	keys->mouse_x = WINDOW_WIDTH / 2;
	keys->mouse_y = WINDOW_HEIGHT / 2;
}

int	check_corner(double x, double y, t_mlxing *mlx)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(x / mlx->map->cell_width);
	grid_y = (int)(y / mlx->map->cell_height);
	if (grid_x < 0 || grid_y < 0 || grid_x >= mlx->map->map_width
		|| grid_y >= mlx->map->map_height)
		return (1);
	return (mlx->map->grid[grid_y][grid_x] == '1'
		|| mlx->map->grid[grid_y][grid_x] == 'D');
}

int	check_wall_collision2(double x, double y, t_mlxing *mlx)
{
	double	padding;

	padding = 10.0;
	return (check_corner(x - padding, y - padding, mlx) || check_corner(x
			+ padding, y - padding, mlx) || check_corner(x - padding, y
			+ padding, mlx) || check_corner(x + padding, y + padding, mlx));
}

void	update_player_grid(int new_center_x, int new_center_y, t_player *player,
		t_mlxing *mlx)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(player->center_x / mlx->map->cell_width);
	grid_y = (int)(player->center_y / mlx->map->cell_height);
	if (grid_x >= 0 && grid_x < mlx->map->map_width && grid_y >= 0
		&& grid_y < mlx->map->map_height
		&& mlx->map->grid[grid_y][grid_x] == '0')
	{
		player->center_x = new_center_x;
		player->center_y = new_center_y;
		player->x = grid_x;
		player->y = grid_y;
	}
}
