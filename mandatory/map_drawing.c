#include "cub3d.h"

static t_textures	*get_current_texture(t_ray *ray, t_map *map)
{
	if (ray->hit_vertical)
	{
		if (ray->is_right)
			return (map->textures[2]);
		else
			return (map->textures[3]);
	}
	else
	{
		if (ray->is_up)
			return (map->textures[0]);
		else
			return (map->textures[1]);
	}
}

static double	calculate_wall_x(t_ray *ray)
{
	double	wall_x;

	if (ray->hit_vertical)
		wall_x = ray->wall_hit_y / (double)CELL_SIZE;
	else
		wall_x = ray->wall_hit_x / (double)CELL_SIZE;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	render_3d_view(t_mlxing *mlx)
{
	t_ray		*ray;
	t_textures	*current_tex;
	double		wall_strip_height;
	double		wall_x;

	int (wall_bottom), (wall_top), (i), (tex_x);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray = &mlx->rays[i];
		wall_strip_height = (CELL_SIZE / ray->ray_distance) * mlx->ppd;
		wall_bottom = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		wall_top = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		current_tex = get_current_texture(ray, mlx->map);
		wall_x = calculate_wall_x(ray);
		tex_x = (int)(wall_x * current_tex->image->width);
		draw_textured_strip(mlx, i, wall_top, wall_bottom,
			(t_draw_params){tex_x, current_tex->image, wall_strip_height});
		i++;
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
	mlx->image->img = mlx_new_image(mlx->mlx_connect,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->image->addr = mlx_get_data_addr(mlx->image->img, &mlx->image->bpp,
			&mlx->image->line_length, &mlx->image->endian);
	mlx->map->cell_height = CELL_SIZE;
	mlx->map->cell_width = CELL_SIZE;
	mlx->map->player->center_x = mlx->map->player->x * mlx->map->cell_width
		+ mlx->map->cell_width / 2;
	mlx->map->player->center_y = mlx->map->player->y * mlx->map->cell_height
		+ mlx->map->cell_height / 2;
	draw_3d_scene(mlx);
	mlx_put_image_to_window(mlx->mlx_connect, mlx->mlx_window,
		mlx->image->img, 0, 0);
}

void	redraw_3d_grid(t_mlxing *mlx)
{
	draw_3d_scene(mlx);
	mlx_put_image_to_window(mlx->mlx_connect, mlx->mlx_window,
		mlx->image->img, 0, 0);
}
