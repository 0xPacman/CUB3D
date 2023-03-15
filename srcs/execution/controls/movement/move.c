/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:12:07 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/15 12:55:12 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void    move_forward(t_engine *engine) {
    t_point pos;
    
    pos.x = (int)(engine->player.pos.x);
    pos.y = (int)(engine->player.pos.y + engine->player.dir.y * engine->player.move_speed);
    if (engine->map[(int)pos.y][(int)pos.x] != '1' && engine->map[(int)pos.y][(int)pos.x] != 'D') {
        engine->player.pos.y += engine->player.dir.y * engine->player.move_speed;
    }
    pos.x = (int)(engine->player.pos.x + engine->player.dir.x * engine->player.move_speed);
    pos.y = (int)(engine->player.pos.y);
    if (engine->map[(int)pos.y][(int)pos.x] != '1' && engine->map[(int)pos.y][(int)pos.x] != 'D') {
        engine->player.pos.x += engine->player.dir.x * engine->player.move_speed;
    }
}

void    move_backward(t_engine *engine) {
    t_point pos;
    
    pos.x = (int)(engine->player.pos.x);
    pos.y = (int)(engine->player.pos.y - engine->player.dir.y * engine->player.move_speed);
    if (engine->map[(int)pos.y][(int)pos.x] != '1' && engine->map[(int)pos.y][(int)pos.x] != 'D') {
        engine->player.pos.y -= engine->player.dir.y * engine->player.move_speed;
    }
    pos.x = (int)(engine->player.pos.x - engine->player.dir.x * engine->player.move_speed);
    pos.y = (int)(engine->player.pos.y);
    if (engine->map[(int)pos.y][(int)pos.x] != '1' && engine->map[(int)pos.y][(int)pos.x] != 'D') {
        engine->player.pos.x -= engine->player.dir.x * engine->player.move_speed;
    }
}

void    move_left(t_engine *engine) {
    t_point pos;
    
    pos.x = (int)(engine->player.pos.x - engine->player.dir.y * engine->player.move_speed);
    pos.y = (int)(engine->player.pos.y);
    if (engine->map[(int)pos.y][(int)pos.x] != '1' && engine->map[(int)pos.y][(int)pos.x] != 'D') {
        engine->player.pos.x -= engine->player.dir.y * engine->player.move_speed;
    }
    pos.x = (int)(engine->player.pos.x);
    pos.y = (int)(engine->player.pos.y + engine->player.dir.x * engine->player.move_speed);
    if (engine->map[(int)pos.y][(int)pos.x] != '1' && engine->map[(int)pos.y][(int)pos.x] != 'D') {
        engine->player.pos.y += engine->player.dir.x * engine->player.move_speed;
    }
}

void    move_right(t_engine *engine) {
    t_point pos;
    
    pos.x = (int)(engine->player.pos.x + engine->player.dir.y * engine->player.move_speed);
    pos.y = (int)(engine->player.pos.y);
    if (engine->map[(int)pos.y][(int)pos.x] != '1' && engine->map[(int)pos.y][(int)pos.x] != 'D') {
        engine->player.pos.x += engine->player.dir.y * engine->player.move_speed;
    }
    pos.x = (int)(engine->player.pos.x);
    pos.y = (int)(engine->player.pos.y - engine->player.dir.x * engine->player.move_speed);
    if (engine->map[(int)pos.y][(int)pos.x] != '1' && engine->map[(int)pos.y][(int)pos.x] != 'D') {
        engine->player.pos.y -= engine->player.dir.x * engine->player.move_speed;
    }
}