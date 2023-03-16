/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:07:36 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/16 15:08:34 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_thick_horizontal_line(t_image *img, int x1, int x2, int y)
{
	t_point	p;
	int		x_start;
	int		x_end;
	int		y_start;
	int		y_end;

	x_start = fmin(x1, x2);
	x_end = fmax(x1, x2);
	y_start = y - (20 - 1) / 2;
	y_end = y + 20 / 2;
	p.y = y_start;
	while (p.y <= y_end)
	{
		p.x = x_start;
		while (p.x <= x_end)
		{
			put_pixel(img, p.x, p.y, 0x00FF00);
			p.x++;
		}
		p.y++;
	}
}

void	draw_status_bar(t_engine *engine)
{
	int	bar_height;
	int	bar_offset;
	int	i;
	int	j;

	engine->player.health = 99;
	bar_height = engine->player.health;
	bar_offset = SCREEN_HEIGHT - bar_height;
	i = 0;
	while (i < bar_height)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			put_pixel(&engine->img, j, i + bar_offset, 0x0D4D4D);
			j++;
		}
		i++;
	}
	draw_thick_horizontal_line(&engine->img, 0, SCREEN_WIDTH / 4
		* engine->player.health / 100, (bar_offset + bar_height / 4)
		+ (bar_height / 2) / 2);
}

void	default_face(t_engine *engine, int x, int y)
{
	if (engine->controls.r)
		engine->player.ammo = 100;
	else
	{
		mlx_put_image_to_window(engine->mlx, engine->win,
			engine->gun[0].img, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 200);
		if (engine->which_face_to_draw < 30)
		{
			mlx_put_image_to_window(engine->mlx, engine->win,
				engine->face[0].img, x, y);
			engine->which_face_to_draw++;
		}
		else if (engine->which_face_to_draw < 60)
		{
			mlx_put_image_to_window(engine->mlx, engine->win,
				engine->face[1].img, x, y);
			engine->which_face_to_draw++;
		}
		else
		{
			engine->which_face_to_draw = 0;
			mlx_put_image_to_window(engine->mlx, engine->win,
				engine->face[1].img, x, y);
		}
	}
}

void	draw_face(t_engine *engine, int x, int y)
{
	int	i;

	i = -1;
	if (engine->controls.left)
		i = 2;
	else if (engine->controls.right)
		i = 3;
	else if (engine->controls.space && engine->player.ammo > 0)
	{
		mlx_put_image_to_window(engine->mlx, engine->win, engine->gun[
			engine->which_gun_to_draw % 4].img,
			SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 200);
		engine->player.ammo--;
		engine->which_gun_to_draw++;
		i = 4;
	}
	else
		default_face(engine, x, y);
	if (i != -1)
		mlx_put_image_to_window(engine->mlx, engine->win,
			engine->face[i].img, x, y);
	if (i != 4 && i != -1)
		mlx_put_image_to_window(engine->mlx, engine->win,
			engine->gun[0].img, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 200);
}
