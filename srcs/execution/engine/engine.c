/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:26:55 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/04 17:30:02 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool   init_engine(t_engine *engine) {
    engine->mlx = NULL;
    engine->win = NULL;
    engine->player = NULL;
    engine->ray = NULL;
    engine->controls = NULL;
    engine->player = malloc(sizeof(t_player));
    engine->ray = malloc(sizeof(t_ray));
    engine->controls = malloc(sizeof(t_controls));
    engine->mlx = mlx_init();
    if (engine->mlx && engine->player && engine->ray && engine->controls) {
        engine->win = mlx_new_window(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
        if (engine->win)
            return (true);
    }
    if (engine->win)
        mlx_destroy_window(engine->mlx, engine->win);
    free(engine->player);
    free(engine->ray);
    free(engine->controls);
    return (false);
}

void    start_engine(void) {
    t_engine    *engine;

    engine = malloc(sizeof(t_engine));
    if (engine && init_engine(engine)) {
        
        // for testing purposes
        engine->player->x = 22;
        engine->player->y = 12;
        engine->player->dir_x = -1;
        engine->player->dir_y = 0;
        engine->player->plane_x = 0;
        engine->player->plane_y = 0.66;
        engine->player->move_speed = 0.05;
        engine->player->rot_speed = 0.05;
        

        init_controls(engine);
        game_loop(engine);
        mlx_loop(engine->mlx);
        
    } else {
        free(engine);
        ERROR(INIT_ENGINE);
        exit(EXIT_FAILURE);
    }
}