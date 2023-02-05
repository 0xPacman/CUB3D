/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:34:13 by ahjadani          #+#    #+#             */
/*   Updated: 2023/02/05 14:03:28 by ahjadani         ###   ########.fr       */
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

// keys
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

// screen size
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

// map for testing
extern char map[24][24];
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

typedef struct s_victor {
    int x;
    int y;
}               t_victor;

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
    
}               t_file;

typedef struct s_player {
    float   x;
    float   y;
    float   dir_x;
    float   dir_y;
    float   plane_x;
    float   plane_y;
	float   move_speed;
	float   rot_speed;
}               t_player;

typedef struct s_ray {
    float   camera_x;
    float   ray_dir_x;
    float   ray_dir_y;
    int     map_x;
    int     map_y;
    float   side_dist_x;
    float   side_dist_y;
    float   delta_dist_x;
    float   delta_dist_y;
    float   perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
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
    t_player    *player;
    t_ray       *ray;
    t_controls  *controls;
	t_image     img;
}               t_engine;

// execution functions
void    start_engine(void);
void    init_controls(t_engine *engine);
void    game_loop(t_engine *engine);
void   put_pixel(t_image *img, int x, int y, int color);


// parsing functions
t_file *init_map(int fd);


#endif