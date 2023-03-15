/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_status_door.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:03:09 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/15 17:37:30 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

int	press_key_f(t_engine *engine)
{
	if (engine->door_pos.x != -1 && engine->door_pos.y != -1)
	{
		if (engine->map[(int)engine->door_pos.y]
			[(int)engine->door_pos.x] == 'D')
			engine->map[(int)engine->door_pos.y][(int)engine->door_pos.x] = 'O';
		else if (engine->map[(int)engine->door_pos.y]
			[(int)engine->door_pos.x] == 'O')
			engine->map[(int)engine->door_pos.y][(int)engine->door_pos.x] = 'D';
		engine->door_pos.x = -1;
		engine->door_pos.y = -1;
	}
	return (0);
}
