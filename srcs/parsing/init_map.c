/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:45:17 by ahjadani          #+#    #+#             */
/*   Updated: 2023/02/03 16:06:37 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int parse_rgb(char *line, t_file *file)
{
    (void)file;
    char **splitted;
    if (line[0] == 'F')
    {
        splitted = ft_split(line, ',');
        int i = 0;
        while(splitted[i])
        {
            printf("%s\n", splitted[i]);
            i++;
        }
    }
    return 0;
}

t_file *parse_file(int fd, t_file *file, char *path)
{
    char *line;
    int i;
    
    (void)path;

    i = 0;
    while(file)
    {
        line = get_next_line(fd);
        printf("GNL: %s\n", line);
        parse_rgb(line, file);

        
    }
    return file;
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
        return (ERROR(ALLOCATE_ERROR) , NULL);
    first_init_colors(file);
    file->north = NULL;
    file->south = NULL;
    file->west = NULL;
    file->east = NULL;
    file->map = NULL;
    file->pos_x = 0;
    file->pos_y = 0;
    if (parse_file(fd, file, path))
        return (NULL);
    return file;
}