# include "cub3d.h"

void	draw_2d_scene(t_image *image, t_map *map)
{
	int x,y,i,j;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	image->color = 0;
	map->cell_width = window_WIDTH / (map->map_width - 1);
	map->cell_height = window_HEIGHT / map->map_height;
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width - 1)
		{
			if (map && map->grid && map->grid[i][j] == '1')
				image->color = WHITE;
			else
				image->color = BLACK;
			y = 0;
			while (y < map->cell_height)
			{
				x = 0;
				while (x < map->cell_width)
				{
					if (x == 0 || y == 0 || x == map->cell_width - 1 || y == map->cell_height - 1)
						my_pixel_put((j * map->cell_width) + x, (i * map->cell_height) + y, image, BLACK);
					else
					    my_pixel_put((j * map->cell_width) + x, (i * map->cell_height) + y, image, image->color);
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
}

void draw_red_dot(t_image *image, t_map *map)
{
	int	pixel_x;
	int	pixel_y;
	int	player_x = map->player->center_x;
	int	player_y = map->player->center_y;

    map->player->radius = 10;
    int start_x = -map->player->radius;
    int end_x = map->player->radius;
    
    int x = start_x;
	while (x <= end_x)  // Iterate over the horizontal range
	{
		int y = start_x;
		while (y <= end_x)  // Iterate over the vertical range
		{
			if (pow(x, 2) + pow(y, 2) <= pow(map->player->radius, 2))  // Check if inside circle
			{
				pixel_x = player_x + x;
				pixel_y = player_y + y;
				if (pixel_x >= 0 && pixel_x < window_WIDTH && pixel_y >= 0 && pixel_y < window_HEIGHT)
					my_pixel_put(pixel_x, pixel_y, image, RED);
			}
			y++;
		}
		x++;
	}
}

void	draw_line(int x1, int y1, int x2, int y2, t_image *image, int color)
{
	int delta_x;
	int delta_y;
	int step_x;
	int step_y;
	int err;
	int e2;

	delta_x = abs(x2 - x1);
	delta_y = abs(y2 - y1);
	err = delta_x - delta_y;
	if(x1 < x2)
		step_x = 1;
	else
		step_x = -1;
	if(y1 < y2)
		step_y = 1;
	else
		step_y = -1;
	while (x1 != x2 || y1 != y2)
	{
		my_pixel_put(x1, y1, image, color);
		e2 = 2 * err;
		if (e2 > -delta_y)
		{
			err -= delta_y;
			x1 += step_x;
		}
		if (e2 < delta_x)
		{
			err += delta_x;
			y1 += step_y;
		}
	}
}


void draw_player_direction(t_image *image, t_mlxing *mlx)
{
	int	center_x;
	int	center_y;
	int	line_length;
	int	end_x;
	int	end_y;
	
	center_x = mlx->map->player->center_x;
	center_y = mlx->map->player->center_y;
	line_length = 30;
	end_x = center_x + (int)(cos(mlx->map->player->angle) * line_length);
	end_y = center_y + (int)(sin(mlx->map->player->angle) * line_length);
    draw_line(center_x, center_y, end_x, end_y, image, RED);
}

void draw_player(t_mlxing *mlx)
{
	mlx->map->player->center_x = mlx->map->player->x * mlx->map->cell_width + mlx->map->cell_width / 2;
	mlx->map->player->center_y = mlx->map->player->y * mlx->map->cell_height + mlx->map->cell_height / 2;
	draw_player_direction(mlx->image, mlx);
	//draw_rays(mlx);
	draw_red_dot(mlx->image, mlx->map);
}
