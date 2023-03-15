/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:51:35 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/15 16:55:07 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_cub(char *filename)
{
	char	**splitted;

	splitted = ft_split(filename, '.');
	if (!splitted)
		return (0);
	if (!ft_strncmp(splitted[ft_tablen(splitted) - 1], "cub", 3))
		return (ft_free_tab(splitted), 1);
	return (ft_free_tab(splitted), 0);
}

int	main(int ac, char **av)
{
	int		fd;
	t_file	*file;

	if (ac != 2 || !check_cub(av[1]))
		return (ERROR(INVALID_ARGS), 2);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ERROR(OPEN_FILE), 2);
	file = init_map(fd);
	close(fd);
	start_engine(file);
	return (0);
}
