/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:42 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/16 13:17:59 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_square(t_engine *engine, t_point *pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(&engine->img, pos->x + j + 20, pos->y + i + 20, color);
			j++;
		}
		i++;
	}
}

void	get_min_max_coordinates(t_engine *engine, int minimap_size,
	t_point *min, t_point *max)
{
	min->x = engine->player.pos.x - (minimap_size / 2);
	min->y = engine->player.pos.y - (minimap_size / 2);
	max->x = min->x + minimap_size - 1;
	max->y = min->y + minimap_size - 3;
	if (min->x < 0)
		min->x = 0;
	if (min->y < 0)
		min->y = 0;
}

void	choice_color(t_engine *engine, t_point *draw, t_point *pos)
{
	if (engine->map[(int)draw->y][(int)draw->x] == '1')
		draw_square(engine, pos, 10, 0x000000);
	else if (engine->map[(int)draw->y][(int)draw->x] == '0')
		draw_square(engine, pos, 10, 0x23c9cf);
	else if (engine->map[(int)draw->y][(int)draw->x] == 'D')
		draw_square(engine, pos, 10, 0xffffff);
	else if (engine->map[(int)draw->y][(int)draw->x] == 'O')
		draw_square(engine, pos, 10, 0x696969);
	else
		draw_square(engine, pos, 10, 0x23c9cf);
}

void	draw_map(t_engine *engine, int minimap_size)
{
	t_point	min;
	t_point	max;
	t_point	pos;
	t_point	draw;

	get_min_max_coordinates(engine, minimap_size, &min, &max);
	draw.y = min.y;
	while (draw.y <= max.y)
	{
		draw.x = min.x;
		while (draw.x <= max.x)
		{
			pos.x = (draw.x - min.x) * 10;
			pos.y = (draw.y - min.y) * 10;
			choice_color(engine, &draw, &pos);
			draw.x++;
		}
		draw.y++;
	}
	pos.x = (engine->player.pos.x - min.x) * 10;
	pos.y = (engine->player.pos.y - min.y) * 10;
	draw_square(engine, &pos, 10, 0xFF0000);
}
