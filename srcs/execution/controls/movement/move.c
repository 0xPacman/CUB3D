/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:12:07 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/06 17:45:24 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void    move_forward(t_engine *engine) {
    t_point pos;
    
    pos.x = (int)(engine->player.pos.x);
    pos.y = (int)(engine->player.pos.y + engine->player.dir.y * engine->player.move_speed);
    if (map[(int)pos.y][(int)pos.x] == '0') {
        engine->player.pos.y += engine->player.dir.y * engine->player.move_speed;
    }
    pos.x = (int)(engine->player.pos.x + engine->player.dir.x * engine->player.move_speed);
    pos.y = (int)(engine->player.pos.y);
    if (map[(int)pos.y][(int)pos.x] == '0') {
        engine->player.pos.x += engine->player.dir.x * engine->player.move_speed;
    }
}

void    move_backward(t_engine *engine) {
    t_point pos;
    
    pos.x = (int)(engine->player.pos.x);
    pos.y = (int)(engine->player.pos.y - engine->player.dir.y * engine->player.move_speed);
    if (map[(int)pos.y][(int)pos.x] == '0') {
        engine->player.pos.y -= engine->player.dir.y * engine->player.move_speed;
    }
    pos.x = (int)(engine->player.pos.x - engine->player.dir.x * engine->player.move_speed);
    pos.y = (int)(engine->player.pos.y);
    if (map[(int)pos.y][(int)pos.x] == '0') {
        engine->player.pos.x -= engine->player.dir.x * engine->player.move_speed;
    }
}

void    move_left(t_engine *engine) {
    t_point pos;
    
    pos.x = (int)(engine->player.pos.x - engine->player.dir.y * engine->player.move_speed);
    pos.y = (int)(engine->player.pos.y);
    if (map[(int)pos.y][(int)pos.x] == '0') {
        engine->player.pos.x -= engine->player.dir.y * engine->player.move_speed;
    }
    pos.x = (int)(engine->player.pos.x);
    pos.y = (int)(engine->player.pos.y + engine->player.dir.x * engine->player.move_speed);
    if (map[(int)pos.y][(int)pos.x] == '0') {
        engine->player.pos.y += engine->player.dir.x * engine->player.move_speed;
    }
}

void    move_right(t_engine *engine) {
    t_point pos;
    
    pos.x = (int)(engine->player.pos.x + engine->player.dir.y * engine->player.move_speed);
    pos.y = (int)(engine->player.pos.y);
    if (map[(int)pos.y][(int)pos.x] == '0') {
        engine->player.pos.x += engine->player.dir.y * engine->player.move_speed;
    }
    pos.x = (int)(engine->player.pos.x);
    pos.y = (int)(engine->player.pos.y - engine->player.dir.x * engine->player.move_speed);
    if (map[(int)pos.y][(int)pos.x] == '0') {
        engine->player.pos.y -= engine->player.dir.x * engine->player.move_speed;
    }
}