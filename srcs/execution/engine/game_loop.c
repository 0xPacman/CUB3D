/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:12:32 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/06 17:46:08 by roudouch         ###   ########.fr       */
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

void draw_rays(t_engine *engine) {
    (void)engine;
}

void   check_controls(t_engine *engine) {
    if (engine->controls.w)
        move_forward(engine);
    if (engine->controls.s)
        move_backward(engine);
    if (engine->controls.a)
        move_left(engine);
    if (engine->controls.d)
        move_right(engine);
    if (engine->controls.left)
        rotate_left(engine);
    if (engine->controls.right)
        rotate_right(engine);
    
}

int frame(t_engine *engine) {
    // clear the window
    mlx_clear_window(engine->mlx, engine->win);

	/// draw mini map
    draw_map(engine);

    // draw the player
    draw_square(engine, engine->player.pos.x * 10, engine->player.pos.y * 10, 10, 0xFF0000);
    
    // check for controls
    check_controls(engine);
    
    // draw rayes on the map from the player
    draw_rays(engine);
    // put the image to the window
    mlx_put_image_to_window(engine->mlx, engine->win, engine->img.img, 0, 0);
    return (0);
}

void    game_loop(t_engine *engine) {
    // init the image
    engine->img.img = mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(engine->img.img, &engine->img.bits_per_pixel, &engine->img.line_length, &engine->img.endian);
    
    // start the game loop
    mlx_loop_hook(engine->mlx, &frame, engine);
}