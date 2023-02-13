/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:12:32 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/13 16:07:05 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void draw_rays(t_engine *engine) {
    (void)engine;
}

int frame(t_engine *engine) {
    // clear the window
    mlx_clear_window(engine->mlx, engine->win);
    
    // check for controls
    check_controls(engine);

    // draw rayes on the map from the player
    start_casting(engine);

	/// draw mini map
    draw_map(engine);

    // draw the player 
    draw_square(engine, engine->player.pos.x * 10, engine->player.pos.y * 10, 10, 0xFF0000);
    
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