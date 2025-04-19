/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:36:59 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/14 21:37:00 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_strip(t_mlxing *mlx, t_ray *ray, int i,
		double wall_strip_height)
{
	t_image	*current_texture;
	int		wall_top;
	int		wall_bottom;
	int		tex_x;
	double	wall_x;

	determine_wall_top_bottom(wall_strip_height, &wall_top, &wall_bottom);
	current_texture = get_texture(mlx, ray);
	wall_x = calculate_wall_x(ray);
	tex_x = (int)(wall_x * current_texture->width);
	draw_textured_strip(i, wall_top, wall_bottom, (t_draw_params){tex_x,
		current_texture, wall_strip_height, ray->hit_vertical, ray->ray_angle,
		ray->ray_distance, mlx});
}

void	render_3d_view(t_mlxing *mlx)
{
	t_ray	*ray;
	double	wall_strip_height;
	int		i;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		ray = &mlx->rays[i];
		wall_strip_height = calculate_wall_strip_height(ray, mlx);
		draw_wall_strip(mlx, ray, i, wall_strip_height);
	}
}

void	draw_3d_scene(t_mlxing *mlx)
{
	mlx->ppd = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	clear_image(mlx->image, BLACK);
	cast_all_rays(mlx);
	render_3d_view(mlx);
}

void	draw_3d_grid(t_mlxing *mlx)
{
	mlx->image->img = mlx_new_image(mlx->mlx_connect, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	mlx->image->addr = mlx_get_data_addr(mlx->image->img, &mlx->image->bpp,
			&mlx->image->line_length, &mlx->image->endian);
	mlx->map->cell_height = CELL_SIZE;
	mlx->map->cell_width = CELL_SIZE;
	mlx->map->player->center_x = mlx->map->player->x * mlx->map->cell_width
		+ mlx->map->cell_width / 2;
	mlx->map->player->center_y = mlx->map->player->y * mlx->map->cell_height
		+ mlx->map->cell_height / 2;
	draw_3d_scene(mlx);
	mlx_put_image_to_window(mlx->mlx_connect, mlx->mlx_window, mlx->image->img,
		0, 0);
}

void	redraw_3d_grid(t_mlxing *mlx)
{
	draw_3d_scene(mlx);
	mlx_put_image_to_window(mlx->mlx_connect, mlx->mlx_window, mlx->image->img,
		0, 0);
}
