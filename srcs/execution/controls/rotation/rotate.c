/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:58:09 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/06 17:42:24 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void   rotate_left(t_engine *engine) {
    double old_dir_x;
    double old_plane_x;

    old_dir_x = engine->player.dir.x;
    old_plane_x = engine->player.plane.x;
    
    engine->player.dir.x = 
        (engine->player.dir.x * cos(engine->player.rot_speed))
        - (engine->player.dir.y * sin(engine->player.rot_speed));
    engine->player.dir.y = 
        (old_dir_x * sin(engine->player.rot_speed))
        + (engine->player.dir.y * cos(engine->player.rot_speed));

    engine->player.plane.x =
        (engine->player.plane.x * cos(engine->player.rot_speed))
        - engine->player.plane.y * sin(engine->player.rot_speed);
    engine->player.plane.y =
        old_plane_x * sin(engine->player.rot_speed)
        + engine->player.plane.y * cos(engine->player.rot_speed);
}

void   rotate_right(t_engine *engine) {
    double old_dir_x;
    double old_plane_x;

    old_dir_x = engine->player.dir.x;
    old_plane_x = engine->player.plane.x;

    engine->player.dir.x =
        engine->player.dir.x * cos(-engine->player.rot_speed)
        - engine->player.dir.y * sin(-engine->player.rot_speed);
    engine->player.dir.y =
        old_dir_x * sin(-engine->player.rot_speed)
        + engine->player.dir.y * cos(-engine->player.rot_speed);
    
    engine->player.plane.x =
        engine->player.plane.x * cos(-engine->player.rot_speed)
        - engine->player.plane.y * sin(-engine->player.rot_speed);
    engine->player.plane.y =
        old_plane_x * sin(-engine->player.rot_speed)
        + engine->player.plane.y * cos(-engine->player.rot_speed);
}