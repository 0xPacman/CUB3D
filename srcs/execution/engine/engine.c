/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:26:55 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/02 17:23:56 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool   init_engine(t_engine *engine) {
    engine = malloc(sizeof(t_engine));
    if (!engine)
        return (false);
    engine->player = malloc(sizeof(t_player));
    if (!engine->player)
        return (false);
    engine->ray = malloc(sizeof(t_ray));
    if (!engine->ray)
        return (false);
    engine->controls = malloc(sizeof(t_controls));
    if (!engine->controls)
        return (false);
    return (true);
}

void    start_engine(void) {
    t_engine    engine;

    if (init_engine(&engine)) {
        
        engine.mlx = mlx_init();
        engine.win = mlx_new_window(engine.mlx, 1920, 1080, "cub3d");
        init_controls(&engine);
        
        mlx_loop(engine.mlx);
        
    } else {
        ft_putstr("Error: Failed to initialize engine!\n");
        exit(EXIT_FAILURE);
    }
}