/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:45:17 by ahjadani          #+#    #+#             */
/*   Updated: 2023/02/03 15:12:06 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_file parse_file(int fd, t_file *file, char *path)
{
    char *line;
    int i;
    
    i = 0;
    while(file)
    {
        line = get_next_line(fd);
        if (!line || !parse_rgb(line, file) || !parse_texture(line, file) || !parse_map(line, file))
            return (print_error(5) , NULL);

    }
}

void   first_init_colors(t_file *file)
{
    file->floor.r = -1;
    file->floor.g = -1;
    file->floor.b = -1;
    file->ceiling.r = -1;
    file->ceiling.g = -1;
    file->ceiling.b = -1;
}

t_file *init_map(int fd, char *path)
{
    t_file *file;
    
    file = malloc(sizeof(t_file));
    if (!file)
        return (print_error(3) , NULL);
    first_init_colors(file);
    file->north = NULL;
    file->south = NULL;
    file->west = NULL;
    file->east = NULL;
    file->map = NULL;
    file->pos_x = 0;
    file->pos_y = 0;
    if (parse_file(fd, file, path) == -1)
        return (NULL);
    
}