#include "cub3d.h"

//void draw_rays(t_mlxing *mlx)
//{
//    double ray_angles[NUM_RAYS];
//    double start_angle = mlx->map->player->angle - (FOV / 2);
//    double ray_step = FOV / NUM_RAYS;

//    for (int i = 0; i < NUM_RAYS; i++)
//    {
//        ray_angles[i] = start_angle + i * ray_step;

//        t_ray ray = cast_ray(mlx, ray_angles[i]);

//        int ray_end_x = mlx->map->player->center_x + cos(ray_angles[i]) * ray.distance;
//        int ray_end_y = mlx->map->player->center_y + sin(ray_angles[i]) * ray.distance;

//        //draw_line(mlx->image, mlx->map->player->center_x, mlx->map->player->center_y, ray_end_x, ray_end_y, WHITE);
//    }
//}

//void draw_rays(t_mlxing *mlx)
//{
//    double player_angle, fov_start, angle_step, max_ray_length;
//    int i;

    
//	max_ray_length = sqrt(pow(mlx->map->map_width * mlx->map->cell_width, 2) + pow(mlx->map->map_height * mlx->map->cell_height, 2));
//    player_angle = mlx->map->player->angle;
//    fov_start = player_angle - (FOV / 2.0);
//    angle_step = FOV / NUM_RAYS;
    
//    // Allocate an array or some structure to store ray distances
//    double ray_distances[NUM_RAYS];

//    i = 0;

//    while (i < NUM_RAYS)
//    {
//        double ray_angle = fov_start + i * angle_step;
//        double ray_dx = cos(ray_angle);
//        double ray_dy = sin(ray_angle);
//        double ray_x = mlx->map->player->center_x;
//        double ray_y = mlx->map->player->center_y;
//        double ray_length = 0.0;
//        int hit_wall = 0;

//        while (!hit_wall && ray_length < max_ray_length)
//        {
//            ray_x += ray_dx * STEP_SIZE;
//            ray_y += ray_dy * STEP_SIZE;
//            ray_length += STEP_SIZE;

//            // Collision detection
//            if (ray_x < 0 || ray_x >= mlx->map->map_width * mlx->map->cell_width ||
//                ray_y < 0 || ray_y >= mlx->map->map_height * mlx->map->cell_height ||
//                mlx->map->grid[(int)(ray_y / mlx->map->cell_height)][(int)(ray_x / mlx->map->cell_width)] == '1')
//            {
//                hit_wall = 1;
//            }
//        }


		
//        // Store the distance for the 3D projection
//		t_ray ray = cast_ray(mlx, ray_angle);
//		ray_distances[i] = ray.distance;
//		//printf("%f\n", ray_distances[i]);
//        //ray_distances[i] = ray_length;
//        // Optionally draw the ray line (for debugging purposes)
//       	//draw_line(mlx->map->player->center_x, mlx->map->player->center_y, ray_x, ray_y, mlx->image, GREEN);

//        i++;
//    }

//    // After casting all rays, render the 3D view using the ray distances
//    render_3d_view(mlx, ray_distances);  // Pass ray distances to the 3D renderer
//}


//void draw_rays(t_mlxing *mlx)
//{
//	double player_angle, fov_start, angle_step, max_ray_length;
//	int i;

//	max_ray_length = sqrt(pow(mlx->map->map_width * mlx->map->cell_width, 2) + pow(mlx->map->map_height * mlx->map->cell_height, 2));
//	player_angle = mlx->map->player->angle;
//	fov_start = player_angle - (FOV / 2.0);
//	angle_step = FOV / NUM_RAYS;
//    i = 0;
//	while (i < NUM_RAYS)
//	{
//		double ray_angle = fov_start + i * angle_step;
//		double ray_dx = cos(ray_angle);
//		double ray_dy = sin(ray_angle);
//		double ray_x = mlx->map->player->center_x;
//		double ray_y = mlx->map->player->center_y;
//		double ray_length = 0.0;
//		int hit_wall = 0;
//		while (!hit_wall && ray_length < max_ray_length)
//		{
//			ray_x += ray_dx * STEP_SIZE;
//			ray_y += ray_dy * STEP_SIZE;
//			ray_length += STEP_SIZE;
//			if (ray_x < 0 || ray_x >= mlx->map->map_width * mlx->map->cell_width ||
//				ray_y < 0 || ray_y >= mlx->map->map_height * mlx->map->cell_height ||
//				mlx->map->grid[(int)(ray_y / mlx->map->cell_height)][(int)(ray_x / mlx->map->cell_width)] == '1')
//			{
//				hit_wall = 1;
//			}
//		}

//		draw_line(mlx->map->player->center_x, mlx->map->player->center_y, ray_x, ray_y, mlx->image, GREEN);
//		i++;
//    }
//}

void redraw_player(t_mlxing *mlx)
{
	draw_player_direction(mlx->image, mlx);
	//draw_rays(mlx);
	draw_red_dot(mlx->image, mlx->map);
}


void draw_2d_grid(t_mlxing *mlx)
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
	draw_2d_scene(mlx->image, mlx->map);
	draw_player(mlx);
	mlx_put_image_to_window(mlx->mlx_connect, mlx->mlx_window, mlx->image->img, 0, 0);
}

void redraw_2d_grid(t_mlxing *mlx)
{
	mlx_clear_window(mlx->mlx_connect, mlx->mlx_window);
	draw_2d_scene(mlx->image, mlx->map);
	redraw_player(mlx);
	printf("redrawn\n");
	mlx_put_image_to_window(mlx->mlx_connect, mlx->mlx_window, mlx->image->img, 0, 0);
}
