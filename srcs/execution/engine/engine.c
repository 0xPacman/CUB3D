/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:26:55 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/03 16:58:10 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool   init_engine(t_engine *engine) {
    engine->player = malloc(sizeof(t_player));
    if (!engine->player)
        return (false);
    engine->ray = malloc(sizeof(t_ray));
    if (!engine->ray) {
        free(engine->player);
        return (false);
    }
    engine->controls = malloc(sizeof(t_controls));
    if (!engine->controls) {
        free(engine->player);
        free(engine->ray);
        return (false);
    }
    return (true);
}

void    start_engine(void) {
    t_engine    *engine;

    engine = malloc(sizeof(t_engine));
    if (engine && init_engine(engine)) {
        
        engine->mlx = mlx_init();
        engine->win = mlx_new_window(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
        init_controls(engine);
        game_loop(engine);
        mlx_loop(engine->mlx);
        
    } else {
        ERROR(INIT_ENGINE);
        exit(EXIT_FAILURE);
    }
}