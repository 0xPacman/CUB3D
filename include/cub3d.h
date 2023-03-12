/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:34:13 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/12 17:50:09 by ahjadani         ###   ########.fr       */
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

// boolean
# define bool int
# define true 1
# define false 0

// Pi
# define PI 3.14159265359

// keys
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

//sides
# define WEST 0
# define EAST 1
# define NORTH 2
# define SOUTH 3

// screen size
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

// map for testing
extern char map[24][24];
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

// texture struct
typedef struct s_texture {
    void    *img;
    char    *data;
    int     bits_per_pixel;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}               t_texture;

typedef struct s_vector {
    float   x;
    float   y;
}               t_vector;

typedef struct s_point {
    float x;
    float y;
}               t_point;

typedef struct rgb {
    int r;
    int g;
    int b;
}               t_rgb;

typedef struct s_file {
    t_rgb    floor;
    t_rgb    ceiling;
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    char    **map;
    float   pos_x;
    float   pos_y;
    int     line_count;
    int     map_len;
    int     flag;
    
}               t_file;

typedef struct s_player {
    t_point     pos;
    t_vector    dir;
    t_vector    plane;
	float       move_speed;
	float       rot_speed;
}               t_player;

typedef struct s_ray {
    float   camera_x;
    t_point dir;
    t_point map;
    t_point side_dist;
    t_point delta_dist;
    float   perp_wall_dist;
    t_point step;
    int     hit;
    int     side;
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     color;
}               t_ray;

typedef struct s_controls {
    int     w;
    int     a;
    int     s;
    int     d;
    int     left;
    int     right;
    int     esc;
}               t_controls;

typedef struct s_image {
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
}               t_image;


typedef struct s_engine {
    void        *mlx;
    void        *win;
    t_player    player;
    t_ray       ray;
    t_controls  controls;
	t_image     img;
    t_texture   *texture;
    t_file      *file;
    t_point     tex_pos;
    float       tex_step;
    float       tex_range;
    char        **map;
}               t_engine;

// execution functions
void    start_engine(t_file *file);
void    init_controls(t_engine *engine);
void    game_loop(t_engine *engine);
void   put_pixel(t_image *img, int x, int y, int color);
// movement functions
void    move_forward(t_engine *engine);
void    move_backward(t_engine *engine);
void    move_left(t_engine *engine);
void    move_right(t_engine *engine);
void    rotate_left(t_engine *engine);
void    rotate_right(t_engine *engine);
void   check_controls(t_engine *engine);
// minimap system functions
void    draw_square(t_engine *engine, int x, int y, int size, int color);
void    draw_map(t_engine *engine);
void    start_casting(t_engine *engine);


// parsing functions
t_file *init_map(int fd);


#endif