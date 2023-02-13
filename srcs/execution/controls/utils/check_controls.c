/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:40:06 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/13 14:40:47 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

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
}