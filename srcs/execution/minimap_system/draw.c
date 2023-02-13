/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:42 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/13 14:37:52 by roudouch         ###   ########.fr       */
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
            put_pixel(&engine->img, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_engine *engine) {
    int x;
    int y;

    y = 0;
    while (y < MAP_HEIGHT) {
        x = 0;
        while (x < MAP_WIDTH) {
            if (map[y][x] == '1')
                draw_square(engine, x * 10, y * 10, 10, 0xB2D6EA);
            else 
                draw_square(engine, x * 10, y * 10, 10, 0x0078BA);
            x++;
        }
        y++;
    }
}