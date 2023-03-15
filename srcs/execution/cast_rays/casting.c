/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:50:05 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/15 16:55:20 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/* 
	x-coordinate in camera space
	calculate ray position and direction
	calculate ray position and direction
	which box of the map we're in
	length of ray from current position to next x or y-side

*/
void	init_vars(t_engine *engine, int x)
{
	engine->ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	engine->ray.dir.x
		= engine->player.dir.x + engine->player.plane.x * engine->ray.camera_x;
	engine->ray.dir.y
		= engine->player.dir.y + engine->player.plane.y * engine->ray.camera_x;
	engine->ray.map.x = (int)engine->player.pos.x;
	engine->ray.map.y = (int)engine->player.pos.y;
	engine->ray.delta_dist.x = fabs(1 / engine->ray.dir.x);
	engine->ray.delta_dist.y = fabs(1 / engine->ray.dir.y);
	engine->ray.hit = 0;
	engine->is_door = 0;
	engine->door_pos.x = -1;
	engine->door_pos.y = -1;
	engine->can_open_door = 0;
	engine->can_close_door = 0;
}

/* 
	calculate step and initial sideDist
*/
void	init_dda(t_engine *engine)
{
	if (engine->ray.dir.x < 0)
	{
		engine->ray.step.x = -1;
		engine->ray.side_dist.x = (engine->player.pos.x
				- engine->ray.map.x) * engine->ray.delta_dist.x;
	}
	else
	{
		engine->ray.step.x = 1;
		engine->ray.side_dist.x = (engine->ray.map.x + 1.0
				- engine->player.pos.x) * engine->ray.delta_dist.x;
	}
	if (engine->ray.dir.y < 0)
	{
		engine->ray.step.y = -1;
		engine->ray.side_dist.y = (engine->player.pos.y
				- engine->ray.map.y) * engine->ray.delta_dist.y;
	}
	else
	{
		engine->ray.step.y = 1;
		engine->ray.side_dist.y = (engine->ray.map.y + 1.0
				- engine->player.pos.y) * engine->ray.delta_dist.y;
	}
}

void	check_hit(t_engine *engine)
{
	if (engine->map[(int)engine->ray.map.y][(int)engine->ray.map.x] == 'O')
	{
		engine->door_pos.x = engine->ray.map.x;
		engine->door_pos.y = engine->ray.map.y;
		if (engine->ray.side_dist.y < 2)
			engine->can_close_door = 1;
	}
	if (engine->map[(int)engine->ray.map.y][(int)engine->ray.map.x] == '1')
		engine->ray.hit = 1;
	if (engine->map[(int)engine->ray.map.y][(int)engine->ray.map.x] == 'D')
	{
		if (engine->ray.side_dist.y < 2)
			engine->can_open_door = 1;
		engine->ray.hit = 1;
		engine->is_door = 1;
		engine->door_pos.x = engine->ray.map.x;
		engine->door_pos.y = engine->ray.map.y;
	}
}

void	perform_dda(t_engine *engine)
{
	while (engine->ray.hit == 0)
	{
		if (engine->ray.side_dist.x < engine->ray.side_dist.y)
		{
			engine->ray.side_dist.x += engine->ray.delta_dist.x;
			engine->ray.map.x += engine->ray.step.x;
			engine->ray.side = 0;
		}
		else
		{
			engine->ray.side_dist.y += engine->ray.delta_dist.y;
			engine->ray.map.y += engine->ray.step.y;
			engine->ray.side = 1;
		}
		check_hit(engine);
	}
}

/*
	Calculate distance projected on camera direction
	(oblique distance will give fisheye effect!)
*/
void	calculate_wall_dist(t_engine *engine)
{
	if (engine->ray.side == 0)
		engine->ray.perp_wall_dist
			= (engine->ray.side_dist.x - engine->ray.delta_dist.x);
	else
		engine->ray.perp_wall_dist
			= (engine->ray.side_dist.y - engine->ray.delta_dist.y);
}

/*
	1.Calculate height of line to draw on screen
	2.calculate lowest and highest pixel to fill in current stripe
*/
void	calculate_line_height(t_engine *engine)
{
	engine->ray.line_height = (int)(SCREEN_HEIGHT / engine->ray.perp_wall_dist);
	engine->ray.draw_start = -engine->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (engine->ray.draw_start < 0)
		engine->ray.draw_start = 0;
	engine->ray.draw_end = engine->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (engine->ray.draw_end >= SCREEN_HEIGHT)
		engine->ray.draw_end = SCREEN_HEIGHT - 1;
}

void	start_casting(t_engine *engine)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_vars(engine, x);
		init_dda(engine);
		perform_dda(engine);
		calculate_wall_dist(engine);
		calculate_line_height(engine);
		draw_wall(engine, x);
		draw_ceil_floor(engine, x);
		x++;
	}
}
