/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:40:06 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/15 12:22:49 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void remove_door_from_map(t_engine *engine)
{
    if (engine->door_pos.x != -1 && engine->door_pos.y != -1)
    {
        engine->map[(int)engine->door_pos.y][(int)engine->door_pos.x] = '0';
        engine->door_pos.x = -1;
        engine->door_pos.y = -1;
    }
}

void   check_controls(t_engine *engine) {
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
    if (engine->controls.f)
        remove_door_from_map(engine);
}