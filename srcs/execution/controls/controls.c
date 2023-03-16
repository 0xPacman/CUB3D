/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:06:22 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/16 22:26:36 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	close_game(t_engine *engine)
{
	mlx_destroy_window(engine->mlx, engine->win);
	freetoclose(engine);
	free(engine);
	engine = NULL;
	exit(EXIT_SUCCESS);
}

int	key_press(int keycode, t_engine *engine)
{
	if (keycode == KEY_ESC)
		close_game(engine);
	if (keycode == KEY_W)
		engine->controls.w = TRUE;
	if (keycode == KEY_S)
		engine->controls.s = TRUE;
	if (keycode == KEY_A)
		engine->controls.a = TRUE;
	if (keycode == KEY_D)
		engine->controls.d = TRUE;
	if (keycode == KEY_LEFT)
		engine->controls.left = TRUE;
	if (keycode == KEY_RIGHT)
		engine->controls.right = TRUE;
	if (keycode == KEY_SPACE)
		engine->controls.space = TRUE;
	if (keycode == KEY_R)
		engine->controls.r = TRUE;
	if (keycode == KEY_F)
		press_key_f(engine);
	return (0);
}

int	key_release(int keycode, t_engine *engine)
{
	if (keycode == KEY_W)
		engine->controls.w = FALSE;
	if (keycode == KEY_S)
		engine->controls.s = FALSE;
	if (keycode == KEY_A)
		engine->controls.a = FALSE;
	if (keycode == KEY_D)
		engine->controls.d = FALSE;
	if (keycode == KEY_LEFT)
		engine->controls.left = FALSE;
	if (keycode == KEY_RIGHT)
		engine->controls.right = FALSE;
	if (keycode == KEY_SPACE)
		engine->controls.space = FALSE;
	if (keycode == KEY_R)
		engine->controls.r = FALSE;
	if (keycode == KEY_F)
		engine->controls.f = FALSE;
	return (0);
}

int	mouse_release(int keycode, int x, int y, t_engine *engine)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		engine->controls.space = FALSE;
	else if (keycode == 2)
	{
		engine->controls.right = FALSE;
		engine->controls.left = FALSE;
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_engine *engine)
{
	int	dx;

	dx = x - SCREEN_WIDTH / 2;
	(void)y;
	if (button == 1)
	{
		engine->controls.space = TRUE;
	}
	else if (button == 2)
	{
		if (dx > 0)
		{
			engine->controls.right = TRUE;
			engine->controls.left = FALSE;
		}
		else
		{
			engine->controls.right = FALSE;
			engine->controls.left = TRUE;
		}
	}
	return (0);
}
