/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:06:22 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/06 14:44:24 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int close_game(t_engine *engine) {
    mlx_destroy_window(engine->mlx, engine->win);
    free(engine->ray);
    engine->ray = NULL;
    free(engine);
    engine = NULL;
    exit(EXIT_SUCCESS);
}

int	key_press(int keycode, t_engine *engine) {
    if (keycode == KEY_ESC)
        close_game(engine);
    if (keycode == KEY_W)
        engine->controls.w = true;
    if (keycode == KEY_S)
        engine->controls.s = true;
    if (keycode == KEY_A)
        engine->controls.a = true;
    if (keycode == KEY_D)
        engine->controls.d = true;
    if (keycode == KEY_LEFT)
        engine->controls.left = true;
    if (keycode == KEY_RIGHT)
        engine->controls.right = true;
    return (0);
}

int	key_release(int keycode, t_engine *engine) {
    if (keycode == KEY_W)
        engine->controls.w = false;
    if (keycode == KEY_S)
        engine->controls.s = false;
    if (keycode == KEY_A)
        engine->controls.a = false;
    if (keycode == KEY_D)
        engine->controls.d = false;
    if (keycode == KEY_LEFT)
        engine->controls.left = false;
    if (keycode == KEY_RIGHT)
        engine->controls.right = false;
	return (0);
}

void init_keys(t_engine *engine) {
	engine->controls.w = false;
	engine->controls.s = false;
	engine->controls.left = false;
	engine->controls.right = false;
}

void init_controls(t_engine *engine) {
	init_keys(engine);
    mlx_hook(engine->win, 2, 1L<<0, key_press, engine);
    mlx_hook(engine->win, 3, 1L<<1, key_release, engine);
    mlx_hook(engine->win, 17, 0, close_game, engine);
}