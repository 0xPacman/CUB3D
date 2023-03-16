/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:52:25 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/16 13:24:21 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_ceil_floor(t_engine *engine, int x)
{
	int	y;

	y = 0;
	while (y < engine->ray.draw_start)
	{
		put_pixel(&engine->img, x, y, create_color(engine->ceiling.r,
				engine->ceiling.g, engine->ceiling.b));
		y++;
	}
	y = engine->ray.draw_end;
	if (!(y < 0))
	{
		while (y < SCREEN_HEIGHT)
		{
			put_pixel(&engine->img, x, y, create_color(engine->floor.r,
					engine->floor.g, engine->floor.b));
			y++;
		}
	}
}

void	draw_wall(t_engine *engine, int x)
{
	int			y;
	t_texture	*texture;

	if (engine->is_door == 1)
		texture = engine->door;
	else
		texture = &engine->texture[check_side(engine)];
	calc_tex_x(engine, texture);
	y = engine->ray.draw_start;
	while (y < engine->ray.draw_end)
	{
		engine->tex_pos.y = (int)engine->tex_range % (texture->height);
		put_pixel(&engine->img, x, y, get_color(texture,
				engine->tex_pos.x, engine->tex_pos.y));
		engine->tex_range += engine->tex_step;
		y = y + 1;
	}
}
