#include "cub3d_bonus.h"

void	minimap_pixel_put(int x, int y, t_image *image, int color)
{
	double	dx;
	double	dy;
	int		pixel_index;

	dx = x - CENTER_X;
	dy = y - CENTER_Y;
	if ((dx * dx + dy * dy) <= MINIMAP_RADIUS * MINIMAP_RADIUS)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			pixel_index = (y * image->line_length) + (x * (image->bpp / 8));
			*(unsigned int *)(image->addr + pixel_index) = color;
		}
	}
}

void	calculate_map_offset(t_mlxing *mlx, double *offset_x, double *offset_y)
{
	double	rel_player_x;
	double	rel_player_y;

	rel_player_x = mlx->map->player->center_x;
	rel_player_y = mlx->map->player->center_y;
	*offset_x = (rel_player_x * MINIMAP_SCALE);
	*offset_y = (rel_player_y * MINIMAP_SCALE);
}

void	draw_minimap_outline(t_image *image, int center_x,
		int center_y, int color)
{
	double	distance;

	int (y), (x), (screen_x), (screen_y);
	y = -MINIMAP_RADIUS - 1;
	while (++y <= MINIMAP_RADIUS)
	{
		x = -MINIMAP_RADIUS - 1;
		while (++x <= MINIMAP_RADIUS)
		{
			distance = sqrt(x * x + y * y);
			if (distance >= MINIMAP_RADIUS - OUTLINE_THICKNESS
				&& distance <= MINIMAP_RADIUS)
			{
				screen_x = center_x + x;
				screen_y = center_y + y;
				if (screen_x >= 0 && screen_x < WINDOW_WIDTH
					&& screen_y >= 0 && screen_y < WINDOW_HEIGHT)
				{
					minimap_pixel_put(screen_x, screen_y, image,
						color);
				}
			}
		}
	}
}

void	draw_background(t_image *image, int center_x, int center_y)
{
	int		y;
	int		x;
	int		screen_x;
	int		screen_y;
	double	distance;

	y = -MINIMAP_RADIUS - 1;
	while (++y <= MINIMAP_RADIUS)
	{
		x = -MINIMAP_RADIUS - 1;
		while (++x <= MINIMAP_RADIUS)
		{
			distance = sqrt(x * x + y * y);
			if (distance <= MINIMAP_RADIUS)
			{
				screen_x = center_x + x;
				screen_y = center_y + y;
				minimap_pixel_put(screen_x, screen_y, image, 0x222222);
			}
		}
	}
}

void	draw_tile(t_mlxing *mlx, int map_x, int map_y)
{
	int	tile_size;
	int	y;
	int	x;
	int	color;

	tile_size = CELL_SIZE * MINIMAP_SCALE;
	y = -1;
	while (++y < tile_size)
	{
		x = -1;
		while (++x < tile_size)
		{
			if (mlx->map->grid[map_y][map_x] == '1')
				color = MINIMAP_COLOR_WALL;
			else
				color = MINIMAP_COLOR_EMPTY;
			minimap_pixel_put(CENTER_X + mlx->tile_x + x,
				CENTER_Y + mlx->tile_y + y,
				mlx->image, color);
		}
	}
}
