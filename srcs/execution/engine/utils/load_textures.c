/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:37:46 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/16 13:49:44 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	load_texture(t_engine *engine, char *path, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(engine->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		error(INVALID_TEXTURE);
	texture->data = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_len, &texture->endian);
}

void	load_faces(t_engine *engine, t_file *file)
{
	load_texture(engine, file->face[0], &engine->face[0]);
	load_texture(engine, file->face[1], &engine->face[1]);
	load_texture(engine, file->face[2], &engine->face[2]);
	load_texture(engine, file->face[3], &engine->face[3]);
	load_texture(engine, file->face[4], &engine->face[4]);
}

void	load_guns(t_engine *engine, t_file *file)
{
	load_texture(engine, file->gun[0], &engine->gun[0]);
	load_texture(engine, file->gun[1], &engine->gun[1]);
	load_texture(engine, file->gun[2], &engine->gun[2]);
	load_texture(engine, file->gun[3], &engine->gun[3]);
}

void	load_gps(t_engine *engine, t_file *file)
{
	load_texture(engine, file->gps[0], &engine->gps[0]);
}

void	load_door(t_engine *engine, t_file *file)
{
	load_texture(engine, file->door[0], &engine->door[0]);
	load_texture(engine, file->open_door[0], &engine->open_door[0]);
	load_texture(engine, file->close_door[0], &engine->close_door[0]);
}
