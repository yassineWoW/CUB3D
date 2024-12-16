#include "cub3d.h"

void	my_pixel_put(int x, int y, t_image *image, int color)
{
	int pixel_index;

	if (x < 0 || x >= window_WIDTH || y < 0 || y >= window_HEIGHT)
    {
        printf("Pixel out of bounds: x=%d, y=%d\n", x, y);
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

t_ray cast_ray(t_mlxing *mlx, double ray_angle)
{
    t_ray ray;
    int start_x = mlx->map->player->center_x;
    int start_y = mlx->map->player->center_y;

    double ray_dx = cos(ray_angle);
    double ray_dy = sin(ray_angle);

    ray.distance = 0;
    ray.hit_wall = 0;

    double ray_length = 0.0;
    int step = 0;

    while (!ray.hit_wall && step < MAX_STEPS)
    {
        int ray_end_x = start_x + ray_dx * ray_length;
        int ray_end_y = start_y + ray_dy * ray_length;
        ray_length += STEP_SIZE;

        if (ray_end_x < 0 || ray_end_x >= mlx->map->map_width * mlx->map->cell_width ||
            ray_end_y < 0 || ray_end_y >= mlx->map->map_height * mlx->map->cell_height ||
            mlx->map->grid[ray_end_y / mlx->map->cell_height][ray_end_x / mlx->map->cell_width] == '1')
        {
            ray.hit_wall = 1;
            ray.distance = ray_length;

            // Check for corners by looking at adjacent cells
            int grid_x = ray_end_x / mlx->map->cell_width;
            int grid_y = ray_end_y / mlx->map->cell_height;

            ray.is_corner = 0;
            if (grid_y > 0 && mlx->map->grid[grid_y - 1][grid_x] == '0')
                ray.is_corner = 1;
            if (grid_y < mlx->map->map_height - 1 && mlx->map->grid[grid_y + 1][grid_x] == '0')
                ray.is_corner = 1;
            if (grid_x > 0 && mlx->map->grid[grid_y][grid_x - 1] == '0')
                ray.is_corner = 1;
            if (grid_x < mlx->map->map_width - 1 && mlx->map->grid[grid_y][grid_x + 1] == '0')
                ray.is_corner = 1;
        }

        step++;
    }

    return ray;
}



//t_ray cast_ray(t_mlxing *mlx, double ray_angle)
//{
//    t_ray ray;
//    int start_x = mlx->map->player->center_x;
//    int start_y = mlx->map->player->center_y;

//    double ray_dx = cos(ray_angle);
//    double ray_dy = sin(ray_angle);

//    ray.distance = 0;
//    ray.hit_wall = 0;

//    double ray_length = 0.0;
//    int step = 0;

//    while (!ray.hit_wall && step < MAX_STEPS)
//    {
//        int ray_end_x = start_x + ray_dx * ray_length;
//        int ray_end_y = start_y + ray_dy * ray_length;
//        ray_length += STEP_SIZE;

//        // Ensure ray doesn't go out of bounds
//        if (ray_end_x < 0 || ray_end_x >= mlx->map->map_width * mlx->map->cell_width ||
//            ray_end_y < 0 || ray_end_y >= mlx->map->map_height * mlx->map->cell_height)
//        {
//            ray.hit_wall = 1;
//            ray.distance = MAX_DISTANCE;  // Set to maximum visible distance
//            break;
//        }

//        // Check for wall hit
//        if (mlx->map->grid[ray_end_y / mlx->map->cell_height][ray_end_x / mlx->map->cell_width] == '1')
//        {
//            ray.hit_wall = 1;
//            ray.distance = ray_length;
//        }

//        step++;
//    }

//    if (step >= MAX_STEPS)
//    {
//        ray.hit_wall = 1;
//        ray.distance = MAX_DISTANCE;  // Avoid infinite rays
//    }

//    return ray;
//}


void draw_vertical_line(t_image *image, int x, int wall_top, int wall_bottom, int color)
{
    for (int y = wall_top; y <= wall_bottom; y++)
    {
        int pattern_color = (y / 10) % 2 == 0 ? color : (color - 0x202020); // Alternating shades
		printf("%d\n", y);
        my_pixel_put(x, y, image, pattern_color);
    }
}



double normalize_angle(double angle)
{
    if (angle < 0)
        angle += 2 * PI;
    if (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

//void render_3d_view(t_mlxing *mlx)
//{
//    int i = 0;
//    while (i < NUM_RAYS)
//    {
//        double ray_angle = normalize_angle(mlx->map->player->angle - (FOV / 2.0) + (i * (FOV / NUM_RAYS)));

//        // Cast the ray and retrieve full collision details
//        t_ray ray = cast_ray(mlx, ray_angle);

//        // Calculate perpendicular distance to avoid fish-eye distortion
//        double perp_distance = ray.distance * cos(ray_angle - mlx->map->player->angle);

//        // Calculate wall height on the projection plane
//        int wall_height = (int)((mlx->map->cell_height / perp_distance) * mlx->ppd);

//        // Determine the start and end points of the vertical line
//        int wall_start = (window_HEIGHT / 2) - (wall_height / 2);
//        int wall_end = (window_HEIGHT / 2) + (wall_height / 2);

//        // Draw the vertical slice of the wall
//        //draw_vertical_line(i, wall_start, wall_end, ray.is_vertical ? DARK_BLUE : WALL_COLOR, mlx);
//		draw_vertical_line(mlx->image, i, wall_start, wall_end, ray.is_vertical ? DARK_BLUE : WALL_COLOR);
//		printf("Ray %d: Angle: %f, Distance: %f\n", i, ray_angle, ray.distance);
//        i++;
//    }
//}


void render_3d_view(t_mlxing *mlx, double ray_distances[NUM_RAYS])
{
    double start_angle = mlx->map->player->angle - (FOV / 2);
    double ray_step = FOV / NUM_RAYS;

    int i = 0;
    while (i < NUM_RAYS)
    {
        double ray_angle = start_angle + i * ray_step;
        t_ray ray = cast_ray(mlx, ray_angle);
        ray_distances[i] = ray.distance;

        // Clamp ray distance to avoid extreme values
        if (ray.distance < 1.0)
            ray.distance = 1.0;
        if (ray.distance > MAX_DISTANCE)
            ray.distance = MAX_DISTANCE;

        // Calculate wall height and positions
        int wall_height = (int)(window_HEIGHT / ray.distance);
        int wall_top = (window_HEIGHT / 2) - (wall_height / 2);
        int wall_bottom = (window_HEIGHT / 2) + (wall_height / 2);

        // Clamp wall positions to screen dimensions
        if (wall_top < 0)
            wall_top = 0;
        if (wall_bottom >= window_HEIGHT)
            wall_bottom = window_HEIGHT - 1;

        // Debugging log
        printf("Ray %d: Distance = %f, Wall Top = %d, Wall Bottom = %d\n", i, ray.distance, wall_top, wall_bottom);

        // Adjust wall color for brightness
        int wall_color = WALL_COLOR;

        // Draw the wall
        draw_vertical_line(mlx->image, i, wall_top, wall_bottom, wall_color);

        // Draw ceiling
        int y = 0;
        while (y < wall_top)
        {
            my_pixel_put(i, y, mlx->image, CEILING_COLOR);
            y++;
        }

        // Draw floor
        y = wall_bottom + 1;
        while (y < window_HEIGHT)
        {
            my_pixel_put(i, y, mlx->image, FLOOR_COLOR);
            y++;
        }

        i++;
    }
}



//void render_3d_view(t_mlxing *mlx, double ray_distances[NUM_RAYS])
//{
//    double start_angle = mlx->map->player->angle - (FOV / 2);
//    double ray_step = FOV / NUM_RAYS;

//    for (int i = 0; i < NUM_RAYS; i++)
//    {
//        double ray_angle = start_angle + i * ray_step;
//        t_ray ray = cast_ray(mlx, ray_angle);
//        ray_distances[i] = ray.distance;

//        // Calculate wall height and positions
//        int wall_height = (int)(window_HEIGHT / ray.distance);
//        int wall_top = (window_HEIGHT / 2) - (wall_height / 2);
//        int wall_bottom = (window_HEIGHT / 2) + (wall_height / 2);

//        if (wall_top < 0)
//            wall_top = 0;
//        if (wall_bottom >= window_HEIGHT)
//            wall_bottom = window_HEIGHT - 1;

//        // Adjust color for shading based on angle difference
//        double angle_difference = fabs(ray_angle - mlx->map->player->angle);
//        double brightness = cos(angle_difference);
//        if (brightness < 0.3)
//            brightness = 0.3;

//        int wall_color = (int)(WALL_COLOR * brightness);

//        // Highlight corners with a distinct color
//        if (ray.is_corner)
//        {
//            wall_color = 0xAAAAAA; // Light gray for corners
//        }

//        // Draw the wall
//        draw_vertical_line(mlx->image, i, wall_top, wall_bottom, wall_color);

//        // Draw ceiling
//        int y = 0;
//        while (y < wall_top)
//        {
//            my_pixel_put(i, y, mlx->image, CEILING_COLOR);
//            y++;
//        }

//        // Draw floor
//        y = wall_bottom + 1;
//        while (y < window_HEIGHT)
//        {
//            my_pixel_put(i, y, mlx->image, FLOOR_COLOR);
//            y++;
//        }
//    }
//}




//void render_3d_view(t_mlxing *mlx, double ray_distances[NUM_RAYS])
//{

//	for (int i = 0; i < NUM_RAYS; i++)
//	{
//	    double ray_distance = ray_distances[i];
	
//	    // Smooth distance to reduce abrupt changes
//	    double adjusted_distance = ray_distance + 0.01;
	
//	    // Calculate smoothed wall height
//	    int wall_height = (int)((window_HEIGHT / adjusted_distance) * 1.5);
//	    int wall_top = (window_HEIGHT / 2) - (wall_height / 2);
//	    int wall_bottom = (window_HEIGHT / 2) + (wall_height / 2);
	
//	    if (wall_top < 0) wall_top = 0;
//	    if (wall_bottom >= window_HEIGHT) wall_bottom = window_HEIGHT - 1;
	
//	    draw_vertical_line(mlx->image, i, wall_top, wall_bottom, WALL_COLOR);
	
//	    // Ceiling and floor remain the same
//	    for (int y = 0; y < wall_top; y++)
//	        my_pixel_put(i, y, mlx->image, CEILING_COLOR);
	
//	    for (int y = wall_bottom; y < window_HEIGHT; y++)
//	        my_pixel_put(i, y, mlx->image, FLOOR_COLOR);
//	}
//}



//void render_3d_view(t_mlxing *mlx, double ray_distances[NUM_RAYS])
//{
//    int i = 0;
//    mlx->ppd = (window_WIDTH / 2) / tan(FOV / 2);
//	while (i < NUM_RAYS)
//    {
//        //double ray_angle = normalize_angle(mlx->map->player->angle - (FOV / 2.0) + (i * (FOV / NUM_RAYS)));
//		double ray_angle = mlx->map->player->angle - (FOV / 2) + (i * (FOV / NUM_RAYS));
//        // Get the ray distance from the array passed from draw_rays
//        double ray_distance = ray_distances[i];

//        // Calculate perpendicular distance to avoid fish-eye distortion
//        double perp_distance = ray_distance * cos(ray_angle - mlx->map->player->angle);

//        // Calculate the wall height on the projection plane
//        int wall_height = (int)((mlx->map->cell_height / perp_distance) * mlx->ppd);
//		//int wall_height = (int)(window_HEIGHT / ray_distances[i] * mlx->ppd);
//		//printf("ppd----------->%d\n", mlx->ppd);
//		//printf("cell------------->%d\n", mlx->map->cell_height);
//		//printf("angle------------->%f\n", ray_angle);
//		//printf("ray_distances------------->%f\n", ray_distances[i]);
//		if (wall_height > window_HEIGHT)
//   			wall_height = window_HEIGHT;
//        // Determine the start and end points of the vertical line to draw
//        int wall_start = (window_HEIGHT / 2) - (wall_height / 2);
//        int wall_end = (window_HEIGHT / 2) + (wall_height / 2);

//		if (wall_start < 0)
//   			wall_start = 0;
//		if (wall_end >= window_HEIGHT)
//    		wall_end = window_HEIGHT - 1;
//         //Draw the vertical slice of the wall
//		 int x = (i * window_WIDTH) / NUM_RAYS;
//		printf("x position----------->%d\n", x);
//       //draw_vertical_line(mlx->image, x, wall_start, wall_end, BLUE);
        
//        i++;
//    }
//}



void	draw_3d_scene(t_mlxing *mlx)
{
	clear_image(mlx->image, YELLOW);
	double ray_distances[NUM_RAYS];
    double start_angle = mlx->map->player->angle - (FOV / 2);
    double ray_step = FOV / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        double ray_angle = start_angle + i * ray_step;
        t_ray ray = cast_ray(mlx, ray_angle);
        ray_distances[i] = ray.distance;
    }
	render_3d_view(mlx, ray_distances);
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
