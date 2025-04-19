/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:13:46 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:56:23 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../LIBFT/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <time.h>
# include <unistd.h>

// window difs	//
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
// math difs	//
# define PI 3.14159265358979323846
// map difs		//
# define WALL_COLOR_NORTH 0x808080
# define WALL_COLOR_SOUTH 0x606060
# define WALL_COLOR_EAST 0x404040
# define WALL_COLOR_WEST 0x202020
# define BLACK 0x000000 // RGB(0, 0, 0)
# define WHITE 0xFFFFFF // RGB(255, 255, 255)
# define RED 0xFF0000   // RGB(255, 0, 0)
# define GREEN 0x00FF00 // RGB(0, 255, 0)
# define BLUE 0x0000FF  // RGB(0, 0, 255)
# define DARK_BLUE 0x00008B
# define YELLOW 0x00FFFF // (0, 255, 255)
# define MAGNETA_BURST 0xFF00FF
# define LIME_SHOCK 0xCCFF00
# define NEON_ORANGE 0xFF6600
# define NEON_TOKYO 0x660066
# define AQUA_DREAM 0x33CCCC
# define HOT_PINK 0xFF6682
# define CYAN 0x00FFFF
# define ELECTRIC_BLUE 0x0066FF
# define GREY 0xBDC3C7
# define UERR "Error\nUsage: ./cub3d maps/*.cub\n"
# define CELL_SIZE 60
# define M_PI 3.14159265358979323846
# define FOV 1.047197551
# define MAX_STEPS 100
# define WALL_COLOR HOT_PINK
# define STEP_SIZE 5.0       // Incremental step size for ray tracing
# define COLLISION_SAMPLES 5 // Number of samples for collision detection
# define PLAYER_RADIUS 3.0
# define MAX_DISTANCE 1000
# define CEILING_COLOR CYAN
# define FLOOR_COLOR GREY
# define MAX_RENDER_DISTANCE 8000.0
# define MINIMAP_RADIUS 80
# define MINIMAP_SCALE 0.2 // Scale factor for minimap size
# define M_TILE_SIZE 1
# define VISIBLE_RANGE 82
# define MINIMAP_COLOR_WALL 0x808080   // Gray for walls
# define MINIMAP_COLOR_EMPTY 0xFFFFFF  // White for empty spaces
# define MINIMAP_COLOR_PLAYER 0xFF0000 // Red for player
# define MINIMAP_COLOR_RAY 0xFFFF00    // Yellow for rays
# define PLAYER_VISION_RADIUS 10
// How far the player can see (in grid cells)
# define MSTEP_SIZE 0.5 // Step size for ray casting
# define OUTLINE_THICKNESS 5
# define RAY_LENGTH 24
# define CENTER_X 700
# define CENTER_Y 100
# define MOUSE_SENSITIVITY 0.005

//      player      //

typedef struct s_player
{
	int					x;
	int					y;
	float				angle;
	char				player_direction;
	int					dir_x;
	int					dir_y;
	int					radius;
	double				center_x;
	double				center_y;
}						t_player;

typedef struct s_keys
{
	int					w_pressed;
	int					s_pressed;
	int					a_pressed;
	int					d_pressed;
	int					left_pressed;
	int					right_pressed;
	int					mouse_x;
	int					mouse_y;
	int					e_pressed;
}						t_keys;

typedef struct s_ray
{
	double				h_wall_hit_x;
	double				h_wall_hit_y;
	double				v_wall_hit_y;
	double				v_wall_hit_x;
	int					hit_vertical;
	int					hit_horizontal;
	int					is_down;
	int					is_up;
	int					is_right;
	int					is_left;
	int					is_corner;
	double				ray_angle;
	double				ray_distance;
	int					wall_hit_x;
	int					wall_hit_y;
	double				start_x;
	double				start_y;
	int					hit;
	double				step_x;
	double				step_y;
	float				wall_stripe_height;
	int					is_door;
	double				door_offset;
	double				tex_x;
}						t_ray;

//	image	//

typedef struct s_colors
{
	int					r;
	int					g;
	int					b;
}						t_colors;

typedef struct s_door
{
	int					x;
	int					y;
	int					is_open;
	double				offset;
}						t_door;

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					color;
	int					bpp;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_image;

//      map elements    //
typedef struct s_textures
{
	t_image				*image;
	char				*name;
}						t_textures;

typedef struct s_map
{
	t_player			*player;
	char				**grid;
	int					floor_color;
	int					ceiling_color;
	char				**map;
	int					map_width;
	int					map_height;
	int					cell_width;
	int					cell_height;
	int					ismap_valid;
	int					n_rows;
	int					door_count;
	t_textures			*textures[5];
	t_door				*doors;
	int					_ismapfound;
	int					_isnewlinefound;

	// Added;
	int					isceiling_color;
	int					isfloor_color;
}						t_map;

typedef struct s_leaks
{
	void				*ptr;
	struct s_leaks		*next;
}						t_leaks;

typedef struct s_animation
{
	t_image				*frames;
	int					frame_count;
	int					current_frame;
	int					is_playing;
	int					loop;
	double				frame_time;
	double				elapsed_time;
}						t_animation;

typedef struct s_mlxing
{
	float				v_x_step;
	float				v_y_step;
	float				v_x_intercept;
	float				v_y_intercept;
	float				v_next_x_touch;
	float				v_next_y_touch;
	int					v_max_iterations;
	float				h_x_step;
	float				h_y_step;
	float				h_x_intercept;
	float				h_y_intercept;
	float				h_next_x_touch;
	float				h_next_y_touch;
	int					h_max_iterations;
	double				new_x;
	double				new_y;
	double				current_x;
	double				current_y;
	double				move_direction_x;
	double				move_direction_y;
	int					s_tile_x;
	int					s_tile_y;
	double				tile_x;
	double				tile_y;
	void				*mlx_connect;
	void				*mlx_window;
	float				ppd;
	int					needs_redraw;
	int					moved;
	int					last_mouse_x;
	int					door_height;
	int					door_width;
	t_map				*map;
	t_image				*image;
	t_image				*door_texture;
	t_ray				*rays;
	t_keys				*keys;
	t_image				*initial_img;
	t_animation			*shoot_animation;
}						t_mlxing;

typedef struct s_draw_params
{
	int					tex_x;
	t_image				*texture;
	double				wall_height;
	int					is_door;
	int					door_offset;
	int					hit_vertical;
	double				ray_angle;
	double				ray_distance;
	t_mlxing			*mlx;
}						t_draw_params;

typedef struct s_wall_strip_params
{
	int					x;
	int					screen_start;
	int					screen_end;
	t_draw_params		params;
	double				step;
	int					sample_interval;
}						t_wall_strip_params;

typedef struct s_utils_
{
	int					screen_start;
	int					screen_end;
	double				step;
	int					sample_interval;
	t_wall_strip_params	strip;
}						t_utils_;

typedef struct s_utils
{
	int					y;
	int					tex_y;
	unsigned int		color;
	double				tex_pos;
	int					j;
}						t_utils;

//---------general use prototypes--------------//
int						init_mlx(t_mlxing *mlx);
void					capture_events(t_mlxing *mlx);
int						exit_game(t_mlxing *mlx, int iscleanexit);
void					my_mlx_error(void);
void					my_pixel_put(int x, int y, t_image *image, int color);
void					clear_image(t_image *image, int color);
double					calculate_distance(double x1, double y1, double x2,
							double y2);
int						check_wall_collision(t_mlxing *mlx, double next_y_touch,
							double next_x_touch);
double					normalize_angle(double angle);
// void	init_player(t_mlxing *mlx);

void					keyinit(t_keys *keys);

//-------------3D rendering functions ------------//
int						is_collision(double new_x, double new_y, t_mlxing *mlx);
void					draw_3d_grid(t_mlxing *mlx);
void					render_3d_view(t_mlxing *mlx);
void					cast_ray(t_mlxing *mlx, t_ray *ray);
void					cast_rays(t_mlxing *mlx);
void					redraw_3d_grid(t_mlxing *mlx);
// int		update_player(void *param);
int						check_wall_collision(t_mlxing *mlx, double next_y_touch,
							double next_x_touch);
void					calculate_horizontal_step(t_ray *ray, t_mlxing *mlx);
void					initialize_horizontal_intercept(t_mlxing *mlx,
							t_ray *ray);
float					find_horizontal_hit(t_mlxing *mlx, t_ray *ray);
float					horizontal_inter(t_mlxing *mlx, t_ray *ray);
float					vertical_inter(t_mlxing *mlx, t_ray *ray);
float					find_vertical_hit(t_mlxing *mlx, t_ray *ray);
void					calculate_vertical_step(t_ray *ray, t_mlxing *mlx);
void					initialize_vertical_intercept(t_mlxing *mlx,
							t_ray *ray);
void					cast_all_rays(t_mlxing *mlx);
void					init_ray(t_ray *ray);
int						is_collision(double new_x, double new_y, t_mlxing *mlx);
int						try_sliding(t_mlxing *mlx);
int						check_collision(t_mlxing *mlx);
int						check_collision_at_angle(double angle, t_mlxing *mlx);
void					calculate_move_direction(t_mlxing *mlx,
							double *move_direction_x, double *move_direction_y);
int						check_wall_collision2(double x, double y,
							t_mlxing *mlx);
void					update_player_grid(int new_center_x, int new_center_y,
							t_player *player, t_mlxing *mlx);
//--------------------events---------------------//
int						key_press(int key, t_mlxing *mlx);
void					keyinit(t_keys *keys);
int						key_release(int key, t_mlxing *mlx);
int						handle_mouse_move(int x, int y, t_mlxing *mlx);
int						handle_rotation(t_mlxing *mlx, double rotate_speed);
void					handle_movement(t_mlxing *mlx, double move_speed,
							double *dx, double *dy);
void					normalize_movement(double *dx, double *dy,
							double move_speed);
int						update_player_position(t_mlxing *mlx, double move_speed,
							double *new_center_x, double *new_center_y);
void					handle_player_movement(t_mlxing *mlx,
							double new_center_x, double new_center_y);
void					handle_redraw(t_mlxing *mlx);
int						update_player(void *param);
void					capture_events(t_mlxing *mlx);
int						init_textures(t_mlxing *mlx);
void					draw_textured_strip(int x, int start_y, int end_y,
							t_draw_params params);
void					draw_minimap_player(t_mlxing *mlx, int center_x,
							int center_y);
void					draw_minimap_rays(t_mlxing *mlx, int center_x,
							int center_y);
void					draw_minimap(t_mlxing *mlx);
void					minimap_pixel_put(int x, int y, t_image *image,
							int color);
void					calculate_map_offset(t_mlxing *mlx, double *offset_x,
							double *offset_y);
void					draw_minimap_outline(t_image *image, int center_x,
							int center_y, int color);
void					draw_background(t_image *image, int center_x,
							int center_y);
void					draw_tile(t_mlxing *mlx, int map_x, int map_y);
void					calc_s_tile(t_mlxing *mlx);
void					draw_map(t_mlxing *mlx);
void					free_parsing(t_mlxing *mlx, int flag);
void					free_parsing_of_exit(t_mlxing *mlx, int flag);
void					free_parsing1(t_mlxing *mlx, int flag);
void					parse_cub(char *file, t_mlxing *mlx);
void					init_player(t_mlxing *mlx);
void					free_dbl_arr(char **s);
void					cleanup_textures(t_mlxing *mlx);
void					cleanup_animation(t_mlxing *mlx, t_animation *anim);
void					clean_stuff(t_mlxing *mlx, t_animation *anim);
void					free_textures_from_anim(t_mlxing *mlx,
							t_animation *anim);
void					free_mlx(t_mlxing *mlx);
void					init_anim_data(t_animation *anim, int frame_count);
//------------------gargbage collector--------------------//

void					cleanup_doors(t_mlxing *mlx);
void					free_lstclear(t_leaks **lst);
void					*ft_malloc(int size, int flag);
//---------------------------------animation-----------------//
void					update_closed_door(t_door *door, double animation_speed,
							char **grid);
void					update_open_door(t_door *door, double animation_speed,
							char **grid);
void					toggle_door_state(t_door *door, char **grid);
int						is_player_in_range(t_door *door, int player_x,
							int player_y, int range);

void					render_animation(t_mlxing *mlx, t_animation *anim,
							int x, int y);
void					update_animation(t_mlxing *mlx, t_animation *anim,
							double delta_time);
void					start_shoot_animation(t_mlxing *mlx);
void					load_animation(t_mlxing *mlx, t_animation *anim,
							const char *folder, int frame_count);
void					render_initial_image(t_mlxing *mlx, int x, int y);
void					load_initial_image(t_mlxing *mlx);
void					start_shoot_animation(t_mlxing *mlx);
void					init_anim(t_animation *anim, int frame_count);
void					free_existing_frames(t_mlxing *mlx, t_animation *anim);
int						init_shoot_anim(t_mlxing *mlx);
int						bound_check(int dx, int dy);
t_door					*find_door_at(t_map *map, int map_x, int map_y);
void					clamp_player_position(t_mlxing *mlx);
void					handle_door_interaction(t_mlxing *mlx);
t_image					*get_current_texture(t_mlxing *mlx, t_ray *ray,
							t_map *map);
double					calculate_wall_x(t_ray *ray);
double					calculate_wall_strip_height(t_ray *ray, t_mlxing *mlx);
void					determine_wall_top_bottom(double wall_strip_height,
							int *wall_top, int *wall_bottom);
t_image					*get_texture(t_mlxing *mlx, t_ray *ray);
int						is_wall_or_closed_door(char cell);
double					calculate_distance2(double x1, double y1, double x2,
							double y2);
void					adjust_p_p(t_player *player, double wall_x,
							double wall_y, double buffer_distance);
//------------------door texture-----------------//
int						check_hit_type(t_mlxing *mlx, t_ray *ray, int map_x,
							int map_y);
void					clean_images_doors(t_mlxing *mlx, int j);
void					destroy_mlx_in_doors(t_mlxing *mlx);
void					door_xpm_fail(t_mlxing *mlx, int i, int j);
void					handle_door_hit(t_ray *ray);
void					calculate_hit_distances(t_mlxing *mlx, t_ray *ray,
							double *horizontal_dist, double *vertical_dist);
// parsing
void					free_parsing1(t_mlxing *mlx, int flag);
void					free_animation_exit(t_mlxing *mlx, int flag);
int						init_textures(t_mlxing *mlx);
void					cleanup_textures(t_mlxing *mlx);
unsigned int			get_textures_pixel(t_image *texture, int x, int y);
int						check_textures_syntax(char *str);
int						parse_textures(char *str, t_map *map);
int						validate_colors_syntax(char *str);
int						convert_rgb_toint(t_colors rgb);
int						is_just_nb_and_space(char *s);
int						fill_rgb(char **s, t_colors *color);
int						count_char(char *s, char c);
int						count_word(char **s);
int						is_map_line(char *str);
int						copy_old_lines(t_map *map, char *str);
int						check_map_syntax(char *str);
char					*remove_char(char *s, char c);
int						parse_map(char *str, t_map *map);
int						is_valid(char *str);
int						all_element_founded(t_map *map);
int						parse_colors(char *str, t_map *map);
int						set_colorsvalue(char *str, t_map *map);
int						is_one_player(t_map *map);
int						check_top_bottom(t_map *map);
int						check_left_right(t_map *map);
int						is_map_closed(t_map *map);
int						is_directory(const char *path);
int						is_opened(char *str);
int						is_textures_accesible(t_map *map);
int						check_colors(t_map *map);
int						get_max_width(t_map *map);
void					free_grid(char **grid, int height);
void					cleanup_doors(t_mlxing *mlx);
int						check_data(t_map *map, t_mlxing *mlx);
void					set_player_angle(t_player *player, char direction);
void					exit_with_error(char *message);
void					init_player(t_mlxing *mlx);
char					**pad_map_grid(char **grid, int map_height,
							int map_width);
void					init_doors(t_mlxing *mlx);
int						count_nb(char c, int *isnbfound);
void					init_doors(t_mlxing *mlx);
void					init_game(t_mlxing *mlx);
int						is_map_closed_from_all(t_map *map);
int						iscolor_clean(char *str);
int						is_directory(const char *path);
int						check_left_right(t_map *map);

#endif