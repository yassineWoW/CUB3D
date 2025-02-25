#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include "../LIBFT/libft.h" 

// window difs	//
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
// math difs	//
# define PI 3.14159265358979323846
// map difs		//
# define WALL_COLOR_NORTH 0x808080
# define WALL_COLOR_SOUTH 0x606060
# define WALL_COLOR_EAST  0x404040
# define WALL_COLOR_WEST  0x202020
# define BLACK	0x000000	// RGB(0, 0, 0)
# define WHITE	0xFFFFFF	// RGB(255, 255, 255)
# define RED		0xFF0000	// RGB(255, 0, 0)					
# define GREEN	0x00FF00	// RGB(0, 255, 0)
# define BLUE	0x0000FF	// RGB(0, 0, 255)
# define DARK_BLUE 0x00008B
# define YELLOW  0x00FFFF    // (0, 255, 255)
# define MAGNETA_BURST 0xFF00FF
# define LIME_SHOCK    0xCCFF00
# define NEON_ORANGE   0xFF6600
# define NEON_TOKYO    0x660066
# define AQUA_DREAM    0x33CCCC
# define HOT_PINK      0xFF6682
# define CYAN		  0x00FFFF
# define ELECTRIC_BLUE 0x0066FF
# define GREY			0xBDC3C7
# define UERR "Error\nUsage: ./cub3d maps/*.cub\n"
# define CELL_SIZE  60
# define NUM_RAYS 800
# define M_PI		3.14159265358979323846
# define FOV 1.047197551
# define MAX_STEPS  100
# define WALL_COLOR HOT_PINK
# define STEP_SIZE 5.0  // Incremental step size for ray tracing
# define COLLISION_SAMPLES 5  // Number of samples for collision detection
# define PLAYER_RADIUS 3.0
# define MAX_DISTANCE 1000
# define CEILING_COLOR CYAN
# define FLOOR_COLOR GREY
# define MAX_RENDER_DISTANCE 8000.0
# define MINIMAP_RADIUS 80
# define MINIMAP_SCALE 0.2  // Scale factor for minimap size
# define M_TILE_SIZE 1
# define VISIBLE_RANGE 82
# define MINIMAP_COLOR_WALL 0x808080  // Gray for walls
# define MINIMAP_COLOR_EMPTY 0xFFFFFF  // White for empty spaces
# define MINIMAP_COLOR_PLAYER 0xFF0000  // Red for player
# define MINIMAP_COLOR_RAY 0xFFFF00  // Yellow for rays
# define PLAYER_VISION_RADIUS 10  // How far the player can see (in grid cells)
# define MSTEP_SIZE 0.5  // Step size for ray casting
# define OUTLINE_THICKNESS  5
# define RAY_LENGTH 24
# define CENTER_X 700
# define CENTER_Y 100
# define MOUSE_SENSITIVITY 0.005

//      player      //

typedef struct s_player
{
	int		x;
	int		y;
	float	angle;
	char	player_direction;
	int		dir_x;
	int		dir_y;
	int		radius;
	double	center_x;
	double	center_y;
}	t_player;

typedef struct s_keys
{
	int	w_pressed;
	int	s_pressed;
	int	a_pressed;
	int	d_pressed;
	int	left_pressed;
	int	right_pressed;
	int	mouse_x;
	int	mouse_y;
}	t_keys;

typedef struct s_ray
{
	double	h_wall_hit_x;
	double	h_wall_hit_y;
	double	v_wall_hit_y;
	double	v_wall_hit_x;
	int		hit_vertical;
	int		hit_horizontal;
	int		is_down;
	int		is_up;
	int		is_right;
	int		is_left;
	int		is_corner;
	double	ray_angle;
	double	ray_distance;
	int		wall_hit_x;
	int		wall_hit_y;
	double	start_x;
	double	start_y;
	int		hit;
	double	step_x;
	double	step_y;
	float	wall_stripe_height;
}	t_ray;

//	image	//

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
}	t_colors;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		color;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_draw_params
{
	int		tex_x;
	t_image	*texture;
	double	wall_height;
}	t_draw_params;

//      map elements    //
typedef struct s_textures
{
	t_image	*image;
	char	*name;
}	t_textures;

typedef struct s_map
{
	t_player	*player;
	char		**grid;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	int			cell_width;
	int			cell_height;
	int			ismap_valid;
	int			n_rows ;
	t_textures	*textures[4];
}	t_map;

//      mlx prerequisite    //


typedef struct s_mlxing
{
	float	v_x_step;
	float	v_y_step;
	float	v_x_intercept;
	float	v_y_intercept;
	float	v_next_x_touch;
	float	v_next_y_touch;
	int		v_max_iterations;
	float	h_x_step;
	float	h_y_step;
	float	h_x_intercept;
	float	h_y_intercept;
	float	h_next_x_touch;
	float	h_next_y_touch;
	int		h_max_iterations;
	double	new_x;
	double	new_y;
	double	current_x;
	double	current_y;
	double	move_direction_x;
	double	move_direction_y;
	int		s_tile_x;
	int		s_tile_y;
	double	tile_x;
	double	tile_y;
	void	*mlx_connect;
	void	*mlx_window;
	float	ppd; // prjection plane distance
	int		needs_redraw;
	int		moved;
	int		last_mouse_x;
	t_map	*map;
	t_image	*image;
	t_ray	*rays;
	t_keys	*keys;
}	t_mlxing;

		//---------general use prototypes--------------//
void	init_mlx(t_mlxing *mlx);
void	capture_events(t_mlxing *mlx);
int		exit_game(t_mlxing *mlx);
void	my_mlx_error(void);
void	my_pixel_put(int x, int y, t_image *image, int color);
void	clear_image(t_image *image, int color);
double	calculate_distance(double x1, double y1, double x2, double y2);
int		check_wall_collision(t_mlxing *mlx, double next_y_touch,
			double next_x_touch);
double	normalize_angle(double angle);
// void	init_player(t_mlxing *mlx);

void	keyinit(t_keys *keys);

		//-------------3D rendering functions ------------//
int		is_collision(double new_x, double new_y, t_mlxing *mlx);
void	draw_3d_grid(t_mlxing *mlx);
void	render_3d_view(t_mlxing *mlx);
void	cast_ray(t_mlxing *mlx, t_ray *ray);
void	cast_rays(t_mlxing *mlx);
void	redraw_3d_grid(t_mlxing *mlx);
//int		update_player(void *param);
int		check_wall_collision(t_mlxing *mlx, double next_y_touch,
			double next_x_touch);
void	calculate_horizontal_step(t_ray *ray, t_mlxing *mlx);
void	initialize_horizontal_intercept(t_mlxing *mlx, t_ray *ray);
float	find_horizontal_hit(t_mlxing *mlx, t_ray *ray);
float	horizontal_inter(t_mlxing *mlx, t_ray *ray);
float	vertical_inter(t_mlxing *mlx, t_ray *ray);
float	find_vertical_hit(t_mlxing *mlx, t_ray *ray);
void	calculate_vertical_step(t_ray *ray, t_mlxing *mlx);
void	initialize_vertical_intercept(t_mlxing *mlx, t_ray *ray);
void	cast_all_rays(t_mlxing *mlx);
void	init_ray(t_ray *ray);
int		is_collision(double new_x, double new_y, t_mlxing *mlx);
int		try_sliding(t_mlxing *mlx);
int		check_collision(t_mlxing *mlx);
int		check_collision_at_angle( double angle, t_mlxing *mlx);
void	calculate_move_direction(t_mlxing *mlx, double *move_direction_x,
			double *move_direction_y);
int		check_wall_collision2(double x, double y, t_mlxing *mlx);
void	update_player_grid(int new_center_x, int new_center_y,
			t_player *player, t_mlxing *mlx);
//--------------------events---------------------//
int		key_press(int key, t_mlxing *mlx);
void	keyinit(t_keys *keys);
int		key_release(int key, t_mlxing *mlx);
//int handle_mouse_move(int x, void *param);
int		handle_mouse_move(int x, int y, t_mlxing *mlx);
int		handle_rotation(t_mlxing *mlx, double rotate_speed);
void	handle_movement(t_mlxing *mlx, double move_speed,
			double *dx, double *dy);
void	normalize_movement(double *dx, double *dy, double move_speed);
int		update_player_position(t_mlxing *mlx, double move_speed,
			double *new_center_x, double *new_center_y);
void	handle_player_movement(t_mlxing *mlx, double new_center_x,
			double new_center_y);
void	handle_redraw(t_mlxing *mlx);
int		update_player(void *param);
void	capture_events(t_mlxing *mlx);
int		init_textures(t_mlxing *mlx);
void	draw_textured_strip(t_mlxing *mlx, int x, int start_y,
			int end_y, t_draw_params params);
void	draw_minimap_player(t_mlxing *mlx, int center_x, int center_y);
void	draw_minimap_rays(t_mlxing *mlx, int center_x, int center_y);
void	draw_minimap(t_mlxing *mlx);
void	minimap_pixel_put(int x, int y, t_image *image, int color);
void	calculate_map_offset(t_mlxing *mlx, double *offset_x, double *offset_y);
void	draw_minimap_outline(t_image *image, int center_x,
			int center_y, int color);
void	draw_background(t_image *image, int center_x, int center_y);
void	draw_tile(t_mlxing *mlx, int map_x, int map_y);
void	calc_s_tile(t_mlxing *mlx);
void	draw_map(t_mlxing *mlx);
void	free_parsing(t_map *map);
void	parse_cub(char *file, t_mlxing *mlx);
void	init_player(t_mlxing *mlx);
void	free_dbl_arr(char **s);
void	cleanup_textures(t_mlxing *mlx);

#endif