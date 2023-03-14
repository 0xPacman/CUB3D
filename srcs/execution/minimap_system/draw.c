/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:42 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/14 18:47:50 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"



void   draw_square(t_engine *engine, int x, int y, int size, int color) {
    int i;
    int j;

    i = 0;
    while (i < size) {
        j = 0;
        while (j < size) {
            put_pixel(&engine->img, x + j+20, y + i+20, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_engine *engine, int minimap_size) {
    int x_min = engine->player.pos.x - (minimap_size / 2);
    int y_min = engine->player.pos.y - (minimap_size / 2);
    int x_max = x_min + minimap_size - 1;
    int y_max = y_min + minimap_size - 3;

    // Make sure that the values are within the boundaries of the map
    x_min = x_min < 0 ? 0 : x_min;
    y_min = y_min < 0 ? 0 : y_min;

    int x;
    int y;

    y = y_min;
    while (y <= y_max) {
        x = x_min;
        while (x <= x_max) {
            int x1 = (x - x_min) * 10;
            int y1 = (y - y_min) * 10;
            if (engine->map[y][x] == '1')
                draw_square(engine, x1, y1, 10, 0x000000);
            else if (engine->map[y][x] == '0')
                draw_square(engine, x1, y1, 10, 0x23c9cf);
            else {
                draw_square(engine, x1, y1, 10, 0x23c9cf);
            }
            x++;
        }
        y++;
    }
    // draw the player position
    draw_square(engine, (engine->player.pos.x - x_min) * 10, (engine->player.pos.y - y_min) * 10, 10, 0xFF0000);
}
