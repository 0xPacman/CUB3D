/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:21:45 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/15 16:41:03 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	map_checker(char **map, t_file *file)
{
	if (!parse_map(map, file))
		ERROR(INVALID_PLAYER);
	if (!check_map_validity(map))
		ERROR(INVALID_MAP);
	return (1);
}

int	check_1_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			i++;
		else if (ft_isspace(line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_mid_lines(char *line)
{
	int	i;
	int	j;

	j = ft_strlen(line) - 1;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isspace(line[j]))
		j--;
	if (line[i] == '1' && line[j] == '1')
		return (1);
	return (0);
}

void	recheck_map(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || i == ft_strlen(map[i])) && !check_1_line(map[i]))
				ERROR(INVALID_MAP);
			else if ((j == 0 || j == ft_strlen(map[i]))
				&& !check_mid_lines(map[i]))
				ERROR(INVALID_MAP);
			j++;
		}
		i++;
	}
}

int	check_for_one(char *line, t_file *file)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	if (len >= 1)
	{
		while (line[i])
		{
			if (line[i] == 'F' || line[i] == 'C')
				return (0);
			if (line[i] == '1')
			{
				return ((file->flag = 1), 1);
			}
			i++;
		}
		if (i == len)
			return (0);
	}
	return (0);
}
