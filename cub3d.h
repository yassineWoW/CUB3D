#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

// window difs	//

#define window_WIDTH 800
#define window_HEIGHT 600

// math difs	//
#define PI 3.14159265358979323846

// map difs		//

# define BLACK	0x000000	// RGB(0, 0, 0)
# define WHITE	0xFFFFFF	// RGB(255, 255, 255)
# define RED		0xFF0000	// RGB(255, 0, 0)					
# define GREEN	0x00FF00	// RGB(0, 255, 0)
# define BLUE	0x0000FF	// RGB(0, 0, 255)
#define DARK_BLUE 0x00008B
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
# define CELL_SIZE  50
# define NUM_RAYS 800
# define M_PI		3.14159265358979323846
# define FOV  (M_PI / 3)
# define MAX_STEPS  100
# define WALL_COLOR HOT_PINK
#define STEP_SIZE 1.0  // Incremental step size for ray tracing
#define COLLISION_SAMPLES 5  // Number of samples for collision detection
#define PLAYER_RADIUS 5.0
# define MAX_DISTANCE 1000

#define CEILING_COLOR CYAN
#define FLOOR_COLOR GREY

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
	int		center_x;
	int		center_y;
}   t_player;

typedef struct s_ray
{
	double hit_x;		// X-coordinate of the wall hit
	double hit_y;		// Y-coordinate of the wall hit
	int is_vertical;
	int hit_vertical;
	float distance;
	int	hit_wall;
	int	is_corner;
		// wheter the line is vertical or horizontal 
}	t_ray;

//	image	//

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


//      map elements    //
typedef struct s_map
{
	t_player	*player;
	char		**grid;
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	int			cell_width;
	int			cell_height;

} t_map;

//      mlx prerequisite    //

typedef struct s_mlxing
{
	void		*mlx_connect;
	void		*mlx_window;
	int			ppd; // prjection plane distance
	t_map		*map;
	t_image		*image;

}	t_mlxing;

		//---------general use prototypes--------------//
void	init_mlx(t_mlxing *mlx);
void	capture_events(t_mlxing *mlx);
int		exit_game(t_mlxing *mlx);
void	my_mlx_error(void);
void	init_map_details(t_mlxing *mlx);
void	my_pixel_put(int x, int y, t_image *image, int color);
void	init_player(t_mlxing *mlx);
int		move_player(int key, t_mlxing *mlx);

		//----------2D rendering functions-------------//

void	draw_2d_scene(t_image *image, t_map *map);
void	draw_2d_grid(t_mlxing *mlx);
void	redraw_2d_grid(t_mlxing *mlx);
//void	redraw_grid(t_mlxing *mlx);
int		rotate_player(int key, t_map *map);
//void	draw_rays(t_mlxing *mlx);
void	draw_line(int x1, int y1, int x2, int y2, t_image *image, int color);
void	draw_red_dot(t_image *image, t_map *map);
void 	draw_player(t_mlxing *mlx);
void	draw_player_direction(t_image *image, t_mlxing *mlx);
void	redraw_player(t_mlxing *mlx);



		//-------------3D rendering functions ------------//

void	draw_3d_grid(t_mlxing *mlx);
void	render_3d_view(t_mlxing *mlx, double ray_distances[NUM_RAYS]);
t_ray	cast_ray(t_mlxing *mlx, double ray_angle);
void	redraw_3d_grid(t_mlxing *mlx);

#endif