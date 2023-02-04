/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:45:17 by ahjadani          #+#    #+#             */
/*   Updated: 2023/02/03 21:11:48 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void ft_split_free(char **split)
{
    int i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

char *ft_rmspaces(char *str)
{
    int i = 0;
    int j = 0;
    char *new;

    new = malloc(sizeof(char) * ft_strlen(str) + 1);
    while (str[i])
    {
        if (!ft_isspace(str[i]))
        {
            new[j] = str[i];
            j++;
        }
        i++;
    }
    return (new);
}

int parse_rgb(char **split_line, t_file *file)
{
    // remove spaces and join all the splitted line into one string
    (void)file;
    // for (int i = 0; split_line[i]; i++)
    //     printf("split_line[%d]:%s \n", i, split_line[i]);
    char *line;
    line = ft_strjoin("", "");
    char **split_rgb;
    int i = 0;
    while (split_line[i])
    {
        line = ft_strjoin(line, split_line[i]);
        i++;
    }
    if (line[0] == 'F')
        split_rgb = ft_split(line, ',');
    else if (line[0] == 'C')
    split_rgb = ft_split(line, ',');
    printf("line:%s \n", line+1);
    return (0);
}

int parse_texture(int fd, t_file *file)
{
    char *line;
    char **split_line;
    while ((line = get_next_line(fd)))
    {
        int i = 0;
        while (ft_isspace(line[i]))
            i++;
        if (line[i] == '\0')
        {
            free(line);
            continue;
        }
        split_line = ft_split(line + i, ' ');
        if (split_line[0][0] == 'W' && split_line[0][1] == 'E')
            file->west = ft_strjoin("", ft_strtrim(split_line[1], " \n\t\v\f\r"));
        else if (split_line[0][0] == 'E' && split_line[0][1] == 'A')
            file->east = ft_strjoin("", ft_strtrim(split_line[1], " \n\t\v\f\r"));
        else if (split_line[0][0] == 'N' && split_line[0][1] == 'O')
            file->north = ft_strjoin("", ft_strtrim(split_line[1], " \n\t\v\f\r"));
        else if (split_line[0][0] == 'S' && split_line[0][1] == 'O')
            file->south = ft_strjoin("", ft_strtrim(split_line[1], " \n\t\v\f\r"));
        else if (split_line[0][0] == 'F' || split_line[0][0] == 'C')
            parse_rgb(split_line, file);
        else
        {
            ft_split_free(split_line);
            free(line);
            return (ERROR(INVALID_TEXTURE) , 1);
        }
    }
    return (0);
}

int parse_file(int fd, t_file *file)
{
    parse_texture(fd, file);
    printf("|NO:%s|\n|SO:%s|\n|EA:%s|\n|WE:%s|\n", file->north, file->south, file->east, file->west);
    printf("|F:%d,%d,%d|\n|C:%d,%d,%d|\n", file->floor.r, file->floor.g, file->floor.b, file->ceiling.r, file->ceiling.g, file->ceiling.b);
    return (1);
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

t_file *init_map(int fd)
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
    if (parse_file(fd, file))
        return (NULL);
    return file;
}