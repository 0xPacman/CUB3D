/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:02:45 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/15 18:15:39 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	init_keys(t_engine *engine)
{
	engine->controls.w = FALSE;
	engine->controls.s = FALSE;
	engine->controls.a = FALSE;
	engine->controls.d = FALSE;
	engine->controls.left = FALSE;
	engine->controls.right = FALSE;
}

void	init_controls(t_engine *engine)
{
	init_keys(engine);
	mlx_hook(engine->win, 2, (1L << 0), key_press, engine);
	mlx_hook(engine->win, 3, 1L << 1, key_release, engine);
	mlx_hook(engine->win, 17, 0, close_game, engine);
	mlx_hook(engine->win, 4, 1L << 2, mouse_press, engine);
	mlx_hook(engine->win, 5, 1L << 3, mouse_release, engine);
}
