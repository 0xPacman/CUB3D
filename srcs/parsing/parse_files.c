/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:09:06 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/16 22:48:48 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_faces(t_file *file)
{
	file->face = malloc(sizeof(t_texture) * 5);
	if (!file->face)
		error(ALLOCATE_ERROR);
	file->face[0] = ft_strdup("textures/face/loop_face.xpm");
	file->face[1] = ft_strdup("textures/face/loop_face1.xpm");
	file->face[2] = ft_strdup("textures/face/left_face.xpm");
	file->face[3] = ft_strdup("textures/face/right_face.xpm");
	file->face[4] = ft_strdup("textures/face/shot.xpm");
}

void	parse_gun(t_file *file)
{
	file->gun = malloc(sizeof(t_texture) * 4);
	if (!file->gun)
		error(ALLOCATE_ERROR);
	file->gun[0] = ft_strdup("textures/gun/gun.xpm");
	file->gun[1] = ft_strdup("textures/gun/gun1.xpm");
	file->gun[2] = ft_strdup("textures/gun/gun2.xpm");
	file->gun[3] = ft_strdup("textures/gun/gun3.xpm");
}

void	parse_gps(t_file *file)
{
	file->gps = malloc(sizeof(t_texture) * 1);
	if (!file->gps)
		error(ALLOCATE_ERROR);
	file->gps[0] = ft_strdup("textures/gps.xpm");
}

void	parse_door(t_file *file)
{
	file->door = malloc(sizeof(t_texture) * 1);
	file->open_door = malloc(sizeof(t_texture) * 1);
	file->close_door = malloc(sizeof(t_texture) * 1);
	if (!file->door || !file->open_door || !file->close_door)
		error(ALLOCATE_ERROR);
	file->door[0] = ft_strdup("textures/door.xpm");
	file->open_door[0] = ft_strdup("textures/open_door.xpm");
	file->close_door[0] = ft_strdup("textures/close_door.xpm");
}

int	parse_file(int fd, t_file *file)
{
	parse_texture(fd, file);
	map_checker(file->map, file);
	map_validator(file->map);
	recheck_map(file->map);
	parse_faces(file);
	parse_gun(file);
	parse_gps(file);
	parse_door(file);
	check_for_0(file->map);
	return (1);
}
