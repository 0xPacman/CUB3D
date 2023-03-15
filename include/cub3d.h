/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:47:03 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/15 18:06:09 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../srcs/parsing/get_next_line/get_next_line.h"
# include "./errors.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// BOOLean
# define BOOL   int
# define TRUE   1
# define FALSE  0

// Pi
# define PI 3.14159265359

// keys
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_R 15
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_F 3

//sides
# define WEST 0
# define EAST 1
# define NORTH 2
# define SOUTH 3

//text size
# define CHAR_HEIGHT 16
# define CHAR_WIDTH 8

// screen size
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

// map for testing
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

// texture struct
typedef struct s_texture {
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		*pixels;
}	t_texture;

typedef struct s_vector {
	float	x;
	float	y;
}	t_vector;

typedef struct s_point {
	float	x;
	float	y;
}	t_point;

typedef struct rgb {
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_file {
	t_rgb		floor;
	t_rgb		ceiling;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		**face;
	char		**gun;
	char		**map;
	char		**gps;
	char		**door;
	char		**open_door;
	char		**close_door;
	float		pos_x;
	float		pos_y;
	int			line_count;
	int			map_len;
	int			flag;
	char		p_dir;
	t_point		p_pos;
}					t_file;

typedef struct s_player {
	t_point		pos;
	t_vector	dir;
	t_vector	plane;
	float		move_speed;
	float		rot_speed;
	int			health;
	int			ammo;
}					t_player;

typedef struct s_ray {
	float		camera_x;
	t_point		dir;
	t_point		map;
	t_point		side_dist;
	t_point		delta_dist;
	float		perp_wall_dist;
	t_point		step;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
}					t_ray;

typedef struct s_controls {
	int	w;
	int	a;
	int	s;
	int	d;
	int	r;
	int	left;
	int	right;
	int	esc;
	int	space;
	int	f;
}					t_controls;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_image;

typedef struct s_engine {
	void			*mlx;
	void			*win;
	t_player		player;
	t_ray			ray;
	t_controls		controls;
	t_image			img;
	t_texture		*texture;
	t_texture		*face;
	t_texture		*gun;
	t_texture		*gps;
	t_texture		*door;
	t_texture		*open_door;
	t_texture		*close_door;
	t_file			*file;
	int				which_face_to_draw;
	int				which_gun_to_draw;
	t_point			tex_pos;
	float			tex_step;
	float			tex_range;
	char			**map;
	t_rgb			floor;
	t_rgb			ceiling;
	int				is_door;
	int				can_open_door;
	int				can_close_door;
	t_point			door_pos;
}					t_engine;
typedef struct s_door
{
	int		top_left_x;
	int		top_left_y;
	int		bottom_right_x;
	int		bottom_right_y;
	int		is_open;
	t_image	texture;
}	t_door;

// execution functions
void			start_engine(t_file *file);
void			init_controls(t_engine *engine);
void			game_loop(t_engine *engine);
void			put_pixel(t_image *img, int x, int y, int color);
// movement functions
void			move_forward(t_engine *engine);
void			move_backward(t_engine *engine);
void			move_left(t_engine *engine);
void			move_right(t_engine *engine);
void			rotate_left(t_engine *engine);
void			rotate_right(t_engine *engine);
void			check_controls(t_engine *engine);
// minimap system functions
void			draw_square(t_engine *engine, int x, int y, int size, int color);
void			draw_map(t_engine *engine, int size);
void			start_casting(t_engine *engine);

unsigned int	get_color(t_texture *t, int x, int y);
// parsing functions
t_file			*init_map(int fd);
int				press_key_f(t_engine *engine);
void			draw_ceil_floor(t_engine *engine, int x);
void			draw_wall(t_engine *engine, int x);
int				check_side(t_engine *engine);
void			calc_tex_x(t_engine *engine, t_texture *texture);
unsigned int	create_color(int r, int g, int b);
unsigned int	get_color(t_texture *t, int x, int y);
void			calculate_wall_dist(t_engine *engine);
void			calculate_line_height(t_engine *engine);

// parse functions
int				parse_file(int fd, t_file *file);
void			parse_door(t_file *file);
void			parse_gps(t_file *file);
void			parse_gun(t_file *file);
void			parse_faces(t_file *file);
int				is0or1(char c);

// texture functions
int				parse_texture(int fd, t_file *file);
void			parse_texture_line(char *line, t_file *file);

// map functions
void			map_reader(char *line, t_file *file);
void			map_validator(char **map);
int				parse_map(char **map, t_file *file);
int				check_map_validity(char **map);
int				map_checker(char **map, t_file *file);
int				check_1_line(char *line);
int				check_mid_lines(char *line);
void			recheck_map(char **map);

// color functions
void			first_init_colors(t_file *file);
void			fill_rgb(char *line, t_file *file);
void			check_rgb_limits(t_file *file);
int				parse_rgb(char **split_line, t_file *file);

// checker functions
int				check_init(t_file *file);
int				check_for_one(char *line, t_file *file);

//control functions
void			init_keys(t_engine *engine);
void			init_controls(t_engine *engine);
int				close_game(t_engine *engine);
int				key_press(int keycode, t_engine *engine);
int				key_release(int keycode, t_engine *engine);
int				mouse_release(int keycode, int x, int y, t_engine *engine);
int				mouse_press(int button, int x, int y, t_engine *engine);
// free functions
void			ft_split_free(char **split);

#endif