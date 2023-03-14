/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:42 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/14 15:33:30 by ahjadani         ###   ########.fr       */
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
    while (engine->map[y]) {
        x = 0;
        while (engine->map[y][x]) {
            if (engine->map[y][x] == '1')
                draw_square(engine, x * 5, y * 5, 5, 0x000000);
            else 
                draw_square(engine, x * 5, y * 5, 5, 0x3E6A2B);
            x++;
        }
        y++;
    }
}