/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:06:22 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/15 17:26:30 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int close_game(t_engine *engine) {
    mlx_destroy_window(engine->mlx, engine->win);
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
    if (keycode == KEY_SPACE)
        engine->controls.space = true;
    if (keycode == KEY_R)
        engine->controls.r = true;
    if (keycode == KEY_F)
        press_key_f(engine);

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
    if (keycode == KEY_SPACE)
        engine->controls.space = false;
    if (keycode == KEY_R)
        engine->controls.r = false;
    if (keycode == KEY_F)
        engine->controls.f = false;
	return (0);
}

int mouse_release(int keycode, int x, int y, t_engine *engine) {
    (void)x;
    (void)y;
    if (keycode == 1)
        engine->controls.space = false; 
    else if (keycode == 2)
    {
        engine->controls.right = false;
        engine->controls.left = false;

    } 
    return (0);
}

void init_keys(t_engine *engine) {
	engine->controls.w = false;
	engine->controls.s = false;
    engine->controls.a = false;
    engine->controls.d = false;
	engine->controls.left = false;
	engine->controls.right = false;
}

int mouse_press(int button, int x, int y, t_engine *engine) {
    int dx = x - SCREEN_WIDTH / 2;
    (void)y;
    // Update the engine controls
    if (button == 1)
    {
        engine->controls.space = true;
    }
    else if (button == 2)
    {
        if (dx > 0) {
            engine->controls.right = true;
            engine->controls.left = false;
        } else {
            engine->controls.right = false;
            engine->controls.left = true;
        }
    }  
    return (0);
}

void init_controls(t_engine *engine) {
	init_keys(engine);
    mlx_hook(engine->win, 2, 1L<<0, key_press, engine);
    mlx_hook(engine->win, 3, 1L<<1, key_release, engine);
    mlx_hook(engine->win, 17, 0, close_game, engine);
    // mouse controls
    mlx_hook(engine->win, 4, 1L<<2, mouse_press, engine);
    mlx_hook(engine->win, 5, 1L<<3, mouse_release, engine);    
}