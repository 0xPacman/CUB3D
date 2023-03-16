/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:45:17 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/16 23:02:19 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	map_reader(char *line, t_file *file)
{
	if (check_init(file))
	{
		if (file->flag == 1 && !check_for_one(line, file))
		{
			file->map[file->map_len] = ft_strdup(line);
			file->map_len++;
		}
		else if (check_for_one(line, file))
		{
			file->map[file->map_len] = ft_strdup(line);
			file->map_len++;
		}
	}
}

int	parse_map(char **map, t_file *file)
{
	int		i;
	int		j;
	int		player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (player_count > 0)
					return (0);
				file->p_dir = map[i][j];
				file->p_pos.x = j;
				file->p_pos.y = i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	return (player_count == 1);
}

t_file	*init_map(int fd)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (error(ALLOCATE_ERROR), NULL);
	first_init_colors(file);
	file->north = NULL;
	file->south = NULL;
	file->west = NULL;
	file->east = NULL;
	file->map = NULL;
	file->pos_x = 0;
	file->pos_y = 0;
	file->line_count = 0;
	file->map_len = 0;
	file->flag = 0;
	file->map = malloc(sizeof(char *) * 10000);
	if (!file->map)
		return (error(ALLOCATE_ERROR), NULL);
	if (!parse_file(fd, file))
		return (NULL);
	return (file);
}

void	check_if_map_endswith0(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
		i++;
	i--;
	j = 0;
	if (ft_strchr("0", map[i][j]) ||
	ft_strnstr(map[i], "101", ft_strlen(map[i])))
		error(INVALID_MAP);
}
