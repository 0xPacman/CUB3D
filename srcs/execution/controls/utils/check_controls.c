/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:40:06 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/16 22:26:50 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	check_controls(t_engine *engine)
{
	if (engine->controls.w)
		move_forward(engine);
	if (engine->controls.s)
		move_backward(engine);
	if (engine->controls.a)
		move_left(engine);
	if (engine->controls.d)
		move_right(engine);
	if (engine->controls.left)
		rotate_left(engine);
	if (engine->controls.right)
		rotate_right(engine);
}

void	freetoclose(t_engine *engine)
{
	free(engine->map);
	free(engine->door);
	free(engine->open_door);
	free(engine->close_door);
	free(engine->texture);
	free(engine->face);
	free(engine->gun);
	free(engine->gps);
}
