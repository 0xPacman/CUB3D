/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:26:55 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/16 13:44:17 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	apply_texture(t_engine *engine, t_file *file)
{
	load_texture(engine, file->west, &engine->texture[WEST]);
	load_texture(engine, file->east, &engine->texture[EAST]);
	load_texture(engine, file->north, &engine->texture[NORTH]);
	load_texture(engine, file->south, &engine->texture[SOUTH]);
	load_faces(engine, file);
	load_guns(engine, file);
	load_gps(engine, file);
	load_door(engine, file);
}

void	start_engine(t_file *file)
{
	t_engine	*engine;
	int			i;

	engine = malloc(sizeof(t_engine));
	if (engine && init_engine(engine))
	{
		engine->map = file->map;
		engine->floor = file->floor;
		engine->ceiling = file->ceiling;
		init_player(engine, file);
		i = 0;
		while (engine->map[i])
		{
			engine->map[i][ft_strlen(engine->map[i]) - 1] = '\0';
			i++;
		}
		init_texture(engine, file);
		init_controls(engine);
		game_loop(engine);
		mlx_loop(engine->mlx);
	}
	else
		error(INIT_ENGINE);
}
