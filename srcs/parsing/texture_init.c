/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:19:20 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/15 16:50:55 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_texture_line(char *line, t_file *file)
{
	char	**split_line;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		line = ft_strdup("[]");
	split_line = ft_split(line + i, ' ');
	if (line[i] == '1' && !check_init(file))
		ERROR(INVALID_MAP);
	else if (split_line[0][0] == 'W' && split_line[0][1] == 'E')
		file->west = ft_strjoin("", ft_strtrim(split_line[1], " \n\t\v\f\r"));
	else if (split_line[0][0] == 'E' && split_line[0][1] == 'A')
		file->east = ft_strjoin("", ft_strtrim(split_line[1], " \n\t\v\f\r"));
	else if (split_line[0][0] == 'N' && split_line[0][1] == 'O')
		file->north = ft_strjoin("", ft_strtrim(split_line[1], " \n\t\v\f\r"));
	else if (split_line[0][0] == 'S' && split_line[0][1] == 'O')
		file->south = ft_strjoin("", ft_strtrim(split_line[1], " \n\t\v\f\r"));
	else if (split_line[0][0] == 'F' || split_line[0][0] == 'C')
		parse_rgb(split_line, file);
	ft_split_free(split_line);
}

int	parse_texture(int fd, t_file *file)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		file->line_count++;
		parse_texture_line(line, file);
		map_reader(line, file);
		free(line);
	}
	return (0);
}
