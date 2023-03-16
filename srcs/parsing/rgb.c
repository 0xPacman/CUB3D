/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:17:58 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/16 13:21:14 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fill_rgb(char *line, t_file *file)
{
	int		*rgb;
	int		i;
	int		count;
	char	**split_rgb;

	count = 0;
	rgb = NULL;
	if (line[0] == 'F')
		rgb = &(file->floor.r);
	else if (line[0] == 'C')
		rgb = &(file->ceiling.r);
	else
		return ;
	split_rgb = ft_split(line + 1, ',');
	i = -1;
	while (++i < 3)
	{
		*(rgb + i) = ft_atoi(split_rgb[i]);
		count++;
	}
	if (count != 3)
		error(INVALID_RGB);
}

void	check_rgb_limits(t_file *file)
{
	if (file->floor.r > 255 || file->floor.r < 0 || file->floor.g > 255
		|| file->floor.g < 0 || file->floor.b > 255 || file->floor.b < 0)
		error(INVALID_RGB);
	if (file->ceiling.r > 255 || file->ceiling.r < 0 || file->ceiling.g > 255
		|| file->ceiling.g < 0 || file->ceiling.b > 255 || file->ceiling.b < 0)
		error(INVALID_RGB);
}

int	parse_rgb(char **split_line, t_file *file)
{
	char	*line;
	int		i;

	line = ft_strjoin("", "");
	i = 0;
	while (split_line[i])
	{
		line = ft_strjoin(line, split_line[i]);
		i++;
	}
	fill_rgb(line, file);
	check_rgb_limits(file);
	return (0);
}

void	first_init_colors(t_file *file)
{
	file->floor.r = 0;
	file->floor.g = 0;
	file->floor.b = 0;
	file->ceiling.r = 0;
	file->ceiling.g = 0;
	file->ceiling.b = 0;
}
