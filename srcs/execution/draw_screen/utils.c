/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:57:07 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/15 16:58:30 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	check_side(t_engine *engine)
{
	if (engine->ray.side == 0)
	{
		if (engine->ray.dir.x > 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (engine->ray.dir.y > 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

void	calc_tex_x(t_engine *engine, t_texture *texture)
{
	float	wall_x;

	if (engine->ray.side == 0)
		wall_x = engine->player.pos.y
			+ engine->ray.perp_wall_dist * engine->ray.dir.y;
	else
		wall_x = engine->player.pos.x
			+ engine->ray.perp_wall_dist * engine->ray.dir.x;
	wall_x -= (int)((wall_x));
	engine->tex_pos.x = (int)(wall_x * (float)texture->width);
	engine->tex_step = (float)texture->height / engine->ray.line_height;
	if (engine->ray.line_height < SCREEN_HEIGHT)
		engine->tex_range = 0;
	else
		engine->tex_range = ((engine->ray.line_height / 2)
				- SCREEN_HEIGHT / 2) * engine->tex_step;
}

unsigned int	create_color(int r, int g, int b)
{
	return (((((unsigned char)r) << 16)
			+ (((unsigned char)g) << 8) + ((unsigned char)b)));
}

unsigned int	get_color(t_texture *t, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = (y * t->line_len) + (x * (t->bits_per_pixel / 8));
	ptr = t->data + pixel;
	return (create_color(ptr[2], ptr[1], ptr[0]));
}