/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:34:13 by ahjadani          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/02 21:07:45 by ahjadani         ###   ########.fr       */
=======
/*   Updated: 2023/02/02 17:31:20 by roudouch         ###   ########.fr       */
>>>>>>> 79e9fbd5223b7c401d461912112d6d5d62f7f72d
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

<<<<<<< HEAD
// parsing functions
void   print_error(int error);
=======
#define bool int
#define true 1
#define false 0

// keys
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53

extern char map[24][24];

typedef struct s_player {
    float   x;
    float   y;
    float   dir_x;
    float   dir_y;
    float   plane_x;
    float   plane_y;
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

typedef struct controls {
    int     w;
    int     a;
    int     s;
    int     d;
    int     left;
    int     right;
    int     esc;
}               t_controls;

typedef struct s_engine {
    void        *mlx;
    void        *win;
    t_player    *player;
    t_ray       *ray;
    t_controls  *controls;
}               t_engine;

// execution
void    start_engine(void);
void    init_controls(t_engine *engine);
int     ESC(t_engine *engine);


>>>>>>> 79e9fbd5223b7c401d461912112d6d5d62f7f72d

#endif