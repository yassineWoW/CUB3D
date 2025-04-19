/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:18:15 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 02:21:00 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_ceiling(int x, int screen_start, t_draw_params params)
{
	int	i;

	i = 0;
	while (i < screen_start)
	{
		my_pixel_put(x, i, params.mlx->image, params.mlx->map->ceiling_color);
		i++;
	}
}

static void	draw_floor(int x, int screen_end, t_draw_params params)
{
	int	i;

	i = screen_end + 1;
	while (i < WINDOW_HEIGHT)
	{
		my_pixel_put(x, i, params.mlx->image, params.mlx->map->floor_color);
		i++;
	}
}

void	draw_wall(t_utils *utils, t_wall_strip_params strip)
{
	utils->tex_y = (int)utils->tex_pos & (strip.params.texture->height - 1);
	utils->color = get_textures_pixel(strip.params.texture, strip.params.tex_x,
			utils->tex_y);
	if (utils->color != 0x00000000)
	{
		my_pixel_put(strip.x, utils->y, strip.params.mlx->image, utils->color);
		utils->j = 1;
		while (utils->j < strip.sample_interval && utils->y
			+ utils->j <= strip.screen_end)
		{
			my_pixel_put(strip.x, utils->y + utils->j, strip.params.mlx->image,
				utils->color);
			utils->j++;
		}
	}
	utils->tex_pos += strip.step * strip.sample_interval;
	utils->y += strip.sample_interval;
}

static void	draw_wall_strip(t_wall_strip_params strip)
{
	t_utils	utils;

	utils.tex_pos = (strip.screen_start - WINDOW_HEIGHT / 2
			+ strip.params.wall_height / 2) * strip.step;
	utils.y = strip.screen_start;
	while (utils.y <= strip.screen_end)
	{
		draw_wall(&utils, strip);
	}
}

void	draw_textured_strip(int x, int start_y, int end_y, t_draw_params params)
{
	t_utils_	utils;

	if (start_y >= WINDOW_HEIGHT || end_y < 0 || x < 0 || x >= WINDOW_WIDTH)
		return ;
	if (start_y < 0)
		utils.screen_start = 0;
	else
		utils.screen_start = start_y;
	if (end_y >= WINDOW_HEIGHT)
		utils.screen_end = WINDOW_HEIGHT - 1;
	else
		utils.screen_end = end_y;
	utils.step = (double)params.texture->height / params.wall_height;
	utils.sample_interval = 1;
	if (params.wall_height > WINDOW_HEIGHT * 2)
		utils.sample_interval = 2;
	draw_ceiling(x, utils.screen_start, params);
	utils.strip = (t_wall_strip_params){x, utils.screen_start, utils.screen_end,
		params, utils.step, utils.sample_interval};
	draw_wall_strip(utils.strip);
	draw_floor(x, utils.screen_end, params);
}
