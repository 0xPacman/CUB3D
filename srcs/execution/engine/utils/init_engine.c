/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:41:51 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/16 13:49:39 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	init_doors_texture(t_engine *engine)
{
	t_texture	*door;
	t_texture	*open_door;
	t_texture	*close_door;

	door = malloc(sizeof(t_texture) * 1);
	open_door = malloc(sizeof(t_texture) * 1);
	close_door = malloc(sizeof(t_texture) * 1);
	if (!door || !open_door || !close_door)
		error(INIT_TEXTURE);
	engine->door = door;
	engine->open_door = open_door;
	engine->close_door = close_door;
}

void	init_texture(t_engine *engine, t_file *file)
{
	t_texture	*texture;
	t_texture	*face;
	t_texture	*gun;
	t_texture	*gps;

	init_doors_texture(engine);
	face = malloc(sizeof(t_texture) * 5);
	texture = malloc(sizeof(t_texture) * 4);
	gun = malloc(sizeof(t_texture) * 4);
	gps = malloc(sizeof(t_texture) * 1);
	if (!texture || !face || !gun || !gps)
		error(INIT_TEXTURE);
	engine->texture = texture;
	engine->face = face;
	engine->gun = gun;
	engine->gps = gps;
	apply_texture(engine, file);
}

BOOL	init_engine(t_engine *engine)
{
	engine->mlx = NULL;
	engine->win = NULL;
	engine->mlx = mlx_init();
	if (engine->mlx)
	{
		engine->win = mlx_new_window(engine->mlx,
				SCREEN_WIDTH, SCREEN_HEIGHT, "HELL3D");
		if (engine->win)
			return (TRUE);
	}
	if (engine->win)
		mlx_destroy_window(engine->mlx, engine->win);
	return (FALSE);
}

void	init_player_dir(char dir, t_engine *engine)
{
	engine->player.dir.y = 0;
	engine->player.dir.x = -1;
	engine->player.plane.x = 0;
	engine->player.plane.y = 0.66;
	if (dir == 'S')
	{
		engine->player.dir.x = 1;
		engine->player.dir.y = 0;
		engine->player.plane.x = 0;
		engine->player.plane.y = -0.66;
	}
	else if (dir == 'E')
	{
		engine->player.dir.x = 0;
		engine->player.dir.y = 1;
		engine->player.plane.x = 0.66;
		engine->player.plane.y = 0;
	}
	else if (dir == 'W')
	{
		engine->player.dir.x = 0;
		engine->player.dir.y = -1;
		engine->player.plane.x = -0.66;
		engine->player.plane.y = 0;
	}
}

void	init_player(t_engine *engine, t_file *file)
{
	engine->player.pos.x = file->p_pos.x;
	engine->player.pos.y = file->p_pos.y;
	init_player_dir(file->p_dir, engine);
	engine->player.move_speed = 0.06;
	engine->player.rot_speed = 0.03;
	engine->player.health = 100;
	engine->player.ammo = 100;
	engine->which_face_to_draw = 0;
	engine->which_gun_to_draw = 0;
}
