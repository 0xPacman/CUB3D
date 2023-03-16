/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:30:32 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/16 19:30:41 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/*
	due to how deltaDist and sideDist were scaled by a factor of
	|rayDir| above, the length of sideDist already almost equals perpWallDist.
	We just need to subtract deltaDist once from it, going one step back
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
