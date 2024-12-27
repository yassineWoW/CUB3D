#include "cub3d.h"

void minimap_pixel_put(int x, int y, t_image *image, int color)
{
    if (x >= 0 && x < window_WIDTH && y >= 0 && y < window_HEIGHT)
    {
        int pixel_index = (y * image->line_length) + (x * (image->bpp / 8));
        *(unsigned int *)(image->addr + pixel_index) = color;
    }
}

void draw_minimap_rect(t_image *image, int x, int y, int width, int height, int color)
{
    int i, j;
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            minimap_pixel_put(x + i, y + j, image, color);
        }
    }
}

void	draw_minimap_player(t_mlxing *mlx)
{
	int player_x;
	int player_y;
	int player_size;

	player_x = mlx->map->player->center_x * MINIMAP_SCALE;
	player_y = mlx->map->player->center_y * MINIMAP_SCALE;
	player_size = 4;  // Size of player on the minimap
	draw_minimap_rect(mlx->image, player_x - player_size / 2, player_y - player_size / 2, player_size, player_size, MINIMAP_COLOR_PLAYER);
}

void	draw_minimap_rays(t_mlxing *mlx)
{
	int 	i;
	int 	step;
	double	start_angle;
    double	ray_step;
	double	ray_angle;
	double	ray_dx;
	double	ray_dy;
	double	ray_x;
	double	ray_y;
	int		grid_x;
	int		grid_y;
	int		screen_x;
	int		screen_y;

	i = 0;
	start_angle = mlx->map->player->angle - (FOV / 2);
	ray_step = FOV / NUM_RAYS;
	while (i < NUM_RAYS)
    {
		step = 0;
		ray_angle = start_angle + i * ray_step;
		ray_dx = cos(ray_angle);
		ray_dy = sin(ray_angle);
		ray_x = mlx->map->player->center_x;
		ray_y = mlx->map->player->center_y;
		while (step < MAX_STEPS)
		{
			ray_x += ray_dx * STEP_SIZE;
			ray_y += ray_dy * STEP_SIZE;
			grid_x = ray_x / mlx->map->cell_width;
			grid_y = ray_y / mlx->map->cell_height;
			// Stop drawing the ray if it hits a wall or goes out of bounds
			if (grid_x < 0 || grid_y < 0 || grid_x >= mlx->map->map_width || grid_y >= mlx->map->map_height ||
			mlx->map->grid[grid_y][grid_x] == '1')
				break;
			screen_x = ray_x * MINIMAP_SCALE;
			screen_y = ray_y * MINIMAP_SCALE;
			minimap_pixel_put(screen_x, screen_y, mlx->image, MINIMAP_COLOR_RAY);
			step++;
		}
		i++;
	}
}

void draw_minimap(t_mlxing *mlx)
{
    int cell_width = mlx->map->cell_width * MINIMAP_SCALE;
    int cell_height = mlx->map->cell_height * MINIMAP_SCALE;
	int	y;
	int x;

	x = 0;
	y = 0;
    // Draw map grid
    while (y < mlx->map->map_height)
    {
		x = 0;
		while (x < mlx->map->map_width)
        {
			int screen_x = x * cell_width;
			int screen_y = y * cell_height;

			if (mlx->map->grid[y][x] == '1')  // Wall
				draw_minimap_rect(mlx->image, screen_x, screen_y, cell_width, cell_height, MINIMAP_COLOR_WALL);
			else  // Empty space
				 draw_minimap_rect(mlx->image, screen_x, screen_y, cell_width, cell_height, MINIMAP_COLOR_EMPTY);
			x++;
		}
		y++;
	}
    // Draw player
    draw_minimap_player(mlx);
    // Draw rays
	draw_minimap_rays(mlx);
}


void	my_pixel_put(int x, int y, t_image *image, int color)
{
	int pixel_index;

	if (x < 0 || x >= window_WIDTH || y < 0 || y >= window_HEIGHT)
    {
        //printf("Pixel out of bounds: x=%d, y=%d\n", x, y);
        return;
    }
	pixel_index = (y * image->line_length) + (x * (image->bpp / 8));
	*(unsigned int *)(image->addr + pixel_index) = color;
}

void clear_image(t_image *image, int color)
{
	int x, y;

	y = 0;
	while (y < window_HEIGHT)
	{
		x = 0;
		while (x < window_WIDTH)
		{
			my_pixel_put(x, y, image, color);
			x++;
		}
		y++;
	}
}


double calculate_distance(double x1, double y1, double x2, double y2)
{
    double distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	//printf("dissss =============== %f\n", distance);
	//printf("x1=================%f\n", x1);
	//printf("x2=================%f\n", x2);
	//printf("y1=================%f\n", y1);
	//printf("y2=================%f\n", y2);
	return distance;
}

int check_wall_collision(t_mlxing *mlx, double next_y_touch, double next_x_touch)
{
    int app_map_x;
    int app_map_y;
    
    // Add boundary checks
    if (next_x_touch < 0 || next_y_touch < 0)
		return 1;

	app_map_x = (int)(next_x_touch / CELL_SIZE);
	app_map_y = (int)(next_y_touch / CELL_SIZE);
    // Check map boundaries
    if (app_map_y >= mlx->map->map_height || app_map_x >= mlx->map->map_width)
        return 1;
        
    return (mlx->map->grid[app_map_y][app_map_x] == '1');
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

float horizontal_inter(t_mlxing *mlx, t_ray *ray)
{
    float x_step, y_step, y_intercept, x_intercept;
    float next_x_touch, next_y_touch, horizontal_hit_distance = 0;

    // Horizontal intersection initialization
    y_step = CELL_SIZE;
    x_step = CELL_SIZE / tan(ray->ray_angle);
    if (ray->is_up)
        y_step *= -1;
    if ((ray->is_left && x_step > 0) || (ray->is_right && x_step < 0))
        x_step *= -1;

    y_intercept = floor(mlx->map->player->center_y / CELL_SIZE) * CELL_SIZE;
    if (ray->is_down)
        y_intercept += CELL_SIZE;
    else if (ray->is_up)
        y_intercept -= 0.0001; // Avoid skipping grid cells on boundary

    x_intercept = mlx->map->player->center_x + (y_intercept - mlx->map->player->center_y) / tan(ray->ray_angle);

    next_x_touch = x_intercept;
    next_y_touch = y_intercept;

    ray->h_wall_hit_x = 0;
    ray->h_wall_hit_y = 0;

    int i = 0, max_iterations = 1000;
    while (next_x_touch >= 0 && next_x_touch <= mlx->map->map_width * CELL_SIZE &&
           next_y_touch >= 0 && next_y_touch <= mlx->map->map_height * CELL_SIZE &&
           i < max_iterations)
    {
        if (is_collision(next_x_touch, next_y_touch, mlx))//check_wall_collision(mlx, next_y_touch, next_x_touch))
        {
            ray->h_wall_hit_x = next_x_touch;
            ray->h_wall_hit_y = next_y_touch;
            horizontal_hit_distance = calculate_distance(mlx->map->player->center_x, mlx->map->player->center_y,
                                                         ray->h_wall_hit_x, ray->h_wall_hit_y);
            printf("Wall hit at x=%f, y=%f with distance=%f\n", ray->h_wall_hit_x, ray->h_wall_hit_y, horizontal_hit_distance);
            break;
        }
        next_x_touch += x_step;
        next_y_touch += y_step;
        i++;
    }

    if (horizontal_hit_distance == 0)
        return 1e30; // Large value for "no hit"
    return horizontal_hit_distance;
}

float vertical_inter(t_mlxing *mlx, t_ray *ray)
{
    float x_step, y_step, x_intercept, y_intercept;
    float next_x_touch, next_y_touch, vertical_hit_distance = 0;

    // Initialize vertical intersection checks
    x_step = CELL_SIZE;
    y_step = tan(ray->ray_angle) * CELL_SIZE;

    // Adjust step direction
    if (ray->is_left)
        x_step *= -1;
    if (ray->is_up && y_step > 0)
        y_step *= -1;
    if (ray->is_down && y_step < 0)
        y_step *= -1;

    // Calculate the first vertical intercept
    x_intercept = floor(mlx->map->player->center_x / CELL_SIZE) * CELL_SIZE;
    if (ray->is_right)
        x_intercept += CELL_SIZE;
    else if (ray->is_left)
        x_intercept -= 0.0001; // Avoid skipping current cell

    y_intercept = mlx->map->player->center_y + (x_intercept - mlx->map->player->center_x) * tan(ray->ray_angle);

    next_x_touch = x_intercept;
    next_y_touch = y_intercept;

    // Initialize hit coordinates
    ray->v_wall_hit_x = 0;
    ray->v_wall_hit_y = 0;

    // Increment through the grid to find intersections
    int i = 0, max_iterations = 1000;
    while (next_x_touch >= 0 && next_x_touch <= mlx->map->map_width * CELL_SIZE &&
           next_y_touch >= 0 && next_y_touch <= mlx->map->map_height * CELL_SIZE &&
           i < max_iterations)
    {
        if (is_collision(next_x_touch, next_y_touch, mlx))//check_wall_collision(mlx, next_y_touch, next_x_touch))
        {
            ray->v_wall_hit_x = next_x_touch;
            ray->v_wall_hit_y = next_y_touch;
            vertical_hit_distance = calculate_distance(mlx->map->player->center_x, mlx->map->player->center_y,
                                                       ray->v_wall_hit_x, ray->v_wall_hit_y);
            printf("Vertical wall hit at x=%f, y=%f with distance=%f\n", ray->v_wall_hit_x, ray->v_wall_hit_y, vertical_hit_distance);
            break;
        }
        next_x_touch += x_step;
        next_y_touch += y_step;
        i++;
    }

    if (vertical_hit_distance == 0)
        return 1e30; // Large value for "no hit"
    return vertical_hit_distance;
}


void cast_ray(t_mlxing *mlx, t_ray *ray)
{
    double horizontal_grid_distance = horizontal_inter(mlx, ray);
    double vertical_grid_distance = vertical_inter(mlx, ray);

    // Determine the closest wall hit
    if (horizontal_grid_distance < vertical_grid_distance)
    {
        ray->wall_hit_x = ray->h_wall_hit_x;
        ray->wall_hit_y = ray->h_wall_hit_y;
        ray->ray_distance = horizontal_grid_distance;
        ray->hit_horizontal = 1;
    }
    else
    {
        ray->wall_hit_x = ray->v_wall_hit_x;
        ray->wall_hit_y = ray->v_wall_hit_y;
        ray->ray_distance = vertical_grid_distance;
        ray->hit_vertical = 1;
    }

    // Perspective correction
    ray->ray_distance *= cos(ray->ray_angle - mlx->map->player->angle);
	if (ray->ray_distance > MAX_RENDER_DISTANCE)
        ray->ray_distance = MAX_RENDER_DISTANCE;
    // Calculate wall stripe height
    ray->wall_stripe_height = (CELL_SIZE / ray->ray_distance) * mlx->ppd;
}

void	init_ray(t_ray *ray)
{
	ray->is_down = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->is_up = !ray->is_down;
	ray->is_right = ray->ray_angle < (M_PI / 2) || ray->ray_angle > M_PI * 1.5;
	ray->is_left = !ray->is_right;
	ray->hit_horizontal = 0;
	ray->hit_vertical = 0;
	ray->h_wall_hit_x = 0;
	ray->h_wall_hit_y = 0;
	ray->v_wall_hit_x = 0;
	ray->v_wall_hit_y = 0;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->ray_distance = 0;
	ray->wall_stripe_height = 0;
}

void	cast_all_rays(t_mlxing *mlx)
{
	t_ray *ray;
	double	ray_angle;
	int		i;

	i = 0;
	ray_angle = mlx->map->player->angle - (FOV / 2);
	while(i < NUM_RAYS)
	{
		ray = &mlx->rays[i];
		ray->ray_angle = normalize_angle(ray_angle);
		init_ray(ray);
		cast_ray(mlx, ray);
		ray_angle += FOV / NUM_RAYS;
		i++;
	}
}

void draw_vertical_line(t_mlxing *mlx, int x, int wall_top, int wall_bottom, int color)
{
	while (wall_top <= wall_bottom)
	{
		my_pixel_put(x, wall_top, mlx->image, color);
		wall_top++;
	}
}


void	render_3d_view(t_mlxing *mlx)
{
	t_ray	*ray;
	double	wall_strip_height;
	int		wall_top;
	int		wall_bottom;
	double	ray_distance;
	int		i;

	i = 0;

	while(i < NUM_RAYS)
	{
		ray = &mlx->rays[i];
		ray_distance = ray->ray_distance;
		wall_strip_height = (CELL_SIZE / ray_distance) * mlx->ppd;
		wall_bottom = (window_HEIGHT / 2) + (wall_strip_height / 2);
		wall_top = (window_HEIGHT / 2) - (wall_strip_height / 2);
		int wall_color;
	if (ray->hit_vertical)
    	wall_color = (ray->is_right) ? WALL_COLOR_EAST : WALL_COLOR_WEST;
	else
    	wall_color = (ray->is_up) ? WALL_COLOR_NORTH : WALL_COLOR_SOUTH;
		draw_vertical_line(mlx, i, 0, wall_top, CEILING_COLOR);
        // Draw wall
        draw_vertical_line(mlx, i, wall_top, wall_bottom, wall_color);
        // Draw floor
        draw_vertical_line(mlx, i, wall_bottom, window_HEIGHT - 1, FLOOR_COLOR);
		i++;
	}

}

void	draw_3d_scene(t_mlxing *mlx)
{
	mlx->ppd = (window_WIDTH / 2) / tan(FOV / 2);
	clear_image(mlx->image, BLACK);
	cast_all_rays(mlx);
	render_3d_view(mlx);
	draw_minimap(mlx);
}

void draw_3d_grid(t_mlxing *mlx)
{
	mlx->image = malloc(sizeof(t_image));
	if (!mlx->image)
	{
		perror("Image allocation failed");
		exit(EXIT_FAILURE);
	}
	mlx->image->img = mlx_new_image(mlx->mlx_connect, window_WIDTH, window_HEIGHT);
	mlx->image->addr = mlx_get_data_addr(mlx->image->img, &mlx->image->bpp,
											&mlx->image->line_length, &mlx->image->endian);
	//draw_2d_scene(mlx->image, mlx->map);
	//draw_player(mlx);
	mlx->map->cell_height = CELL_SIZE;
	mlx->map->cell_width = CELL_SIZE;
	mlx->map->player->center_x = mlx->map->player->x * mlx->map->cell_width + mlx->map->cell_width / 2;
	mlx->map->player->center_y = mlx->map->player->y * mlx->map->cell_height + mlx->map->cell_height / 2;
	draw_3d_scene(mlx);
	mlx_put_image_to_window(mlx->mlx_connect, mlx->mlx_window, mlx->image->img, 0, 0);
}

void redraw_3d_grid(t_mlxing *mlx)
{
	mlx_clear_window(mlx->mlx_connect, mlx->mlx_window);
	draw_3d_scene(mlx);
	//redraw_player(mlx);
	printf("redrawn\n");
	mlx_put_image_to_window(mlx->mlx_connect, mlx->mlx_window, mlx->image->img, 0, 0);
}
