/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:23:38 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/15 16:36:56 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_init(t_file *file)
{
	if (!file->north || !file->south || !file->east || !file->west)
		return (0);
	return (1);
}

int	is0or1(char c)
{
	if (c == '0' || c == '1')
		return (1);
	return (0);
}

void	map_validator(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!is0or1(map[i][j - 1]) && !is0or1(map[i][j + 1])
					&& !is0or1(map[i - 1][j]) && !is0or1(map[i + 1][j]))
					ERROR(INVALID_MAP);
			}
			j++;
		}
		i++;
	}
}

int	check_map_validity(char **map)
{
	int	i;
	int	j;
	int	valid_char;
	int	unvalid_char;

	unvalid_char = 0;
	i = 0;
	valid_char = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW01 \nD", map[i][j]))
				valid_char++;
			else
				unvalid_char++;
			j++;
		}
		i++;
	}
	return (unvalid_char == 0 && valid_char > 0);
}
