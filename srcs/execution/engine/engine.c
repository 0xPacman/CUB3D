/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:26:55 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/13 16:23:52 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool   init_engine(t_engine *engine) {
    engine->mlx = NULL;
    engine->win = NULL;
    engine->mlx = mlx_init();
    if (engine->mlx) {
        engine->win = mlx_new_window(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Wolf4D");
        if (engine->win)
            return (true);
    }
    if (engine->win)
        mlx_destroy_window(engine->mlx, engine->win);
    return (false);
}

void    start_engine(void) {
    t_engine    *engine;

    engine = malloc(sizeof(t_engine));
    if (engine && init_engine(engine)) {
        
        // for testing purposes
        engine->player.pos.x = 22;
        engine->player.pos.y = 12;
        engine->player.dir.x = cos(PI);
        engine->player.dir.y = sin(PI);
        engine->player.plane.x = 0;
        engine->player.plane.y = 0.66;
        engine->player.move_speed = 0.06;
        engine->player.rot_speed = 0.03;
        

        init_controls(engine);
        game_loop(engine);
        mlx_loop(engine->mlx);
        
    } else {
        free(engine);
        ERROR(INIT_ENGINE);
        exit(EXIT_FAILURE);
    }
}