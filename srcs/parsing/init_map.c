/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:45:17 by ahjadani          #+#    #+#             */
/*   Updated: 2023/02/05 13:54:38 by ahjadani         ###   ########.fr       */
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
void fill_rgb(char *line, t_file *file)
{
    char *rgbline;
    char **split_rgb = NULL;
    int i;

    i = 0;
    rgbline = line + 1;
    if (line[0] == 'F')
    {
        split_rgb = ft_split(rgbline, ',');
        i = 0;
        while(split_rgb[i])
        {
            file->floor.r = ft_atoi(split_rgb[0]);
            file->floor.g = ft_atoi(split_rgb[1]);
            file->floor.b = ft_atoi(split_rgb[2]);
            i++;
        }
        if (i != 3)
        {
            ERROR(INVALID_RGB);
            exit(1);
        }
            
    }
    if (line[0] == 'C')
    {
        split_rgb = ft_split(rgbline, ',');
        i = 0;
        while(split_rgb[i])
        {
            file->ceiling.r = ft_atoi(split_rgb[0]);
            file->ceiling.g = ft_atoi(split_rgb[1]);
            file->ceiling.b = ft_atoi(split_rgb[2]);
            i++;
        }
        if (i != 3)
        {
            ERROR(INVALID_RGB);
            exit(1);
        }
    }
}

void check_rgb_limits(t_file *file)
{
    //printf("|F:%d,%d,%d|\n|C:%d,%d,%d|\n", file->floor.r, file->floor.g, file->floor.b, file->ceiling.r, file->ceiling.g, file->ceiling.b);
    if (file->floor.r > 255 || file->floor.r < 0 || file->floor.g > 255 || file->floor.g < 0 || file->floor.b > 255 || file->floor.b < 0)
    {
        ERROR(INVALID_RGB);
        exit(1);
    }
    if (file->ceiling.r > 255 || file->ceiling.r < 0 || file->ceiling.g > 255 || file->ceiling.g < 0 || file->ceiling.b > 255 || file->ceiling.b < 0)
    {
        ERROR(INVALID_RGB);
        exit(1);
    }
}

int parse_rgb(char **split_line, t_file *file)
{
    char *line;
    
    line = ft_strjoin("", "");
    
    int i = 0;
    while (split_line[i])
    {
        line = ft_strjoin(line, split_line[i]);
        i++;
    }
    fill_rgb(line, file);
    check_rgb_limits(file);
    return (0);
}

int check_init(t_file *file)
{
    if (!file->north || !file->south || !file->east || !file->west)
        return (0);
    return (1);
}

int check_for_one(char *line)
{
    int i = 0;
    int len = ft_strlen(line);
    if (len >= 1)
    {
        while (line[i])
        {
            if (line[i] == 'F' || line[i] == 'C')
                return (0);
            if (line[i] == '1')
                return (1);
            i++;
        }
        if (i == len)
            return (0);
    }
    return (0);
}

void map_reader(char *line, t_file *file)
{
    if (check_init(file))
    {
        if (check_for_one(line))
        {
            file->map[file->map_len] = ft_strjoin("", line);
            file->map_len++;
        }
    }
}

int parse_texture(int fd, t_file *file)
{
    char *line;
    char **split_line;
    while ((line = get_next_line(fd)))
    {
        file->line_count++;
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
        }
        map_reader(line, file);
    }
    return (0);
}

int is0or1(char c)
{
    if (c == '0' || c == '1')
        return (1);
    return (0);
}

void map_validator(char **map)
{
    int i = 0;
    int j = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                if (!is0or1(map[i][j - 1]) && !is0or1(map[i][j + 1]) && !is0or1(map[i - 1][j]) && !is0or1(map[i + 1][j]))
                {
                    printf("map error at %d,%d\n", i, j);
                    ERROR(INVALID_MAP);
                    exit(1);
                }
            }
            j++;
        }
        i++;
    }
}



int map_checker(char **map)
{
    int i = 0;
    int j = 0;
    int player_count = 0;
    int valid_char = 0;
    int unvalid_char = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W' 
            || map[i][j] == '0' || map[i][j] == '1' || map[i][j] == ' ' || map[i][j] == '\n')
                valid_char++;
            else
                unvalid_char++;
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
                player_count++;
            j++;
        }
        i++;
    }
    if (unvalid_char != 0 || player_count != 1)
    {
        if (unvalid_char != 0)
            ERROR(INVALID_MAP);
        if (player_count != 1)
            ERROR(INVALID_PLAYER);
        exit(1);
    }
    return (1);
}

void recheck_map(char **map)
{
    // check if there '1' in every line
    int i = 0;
    int j = 0;
    while (map[i])
    {
        printf("line %d: %s\n", i, map[i]);
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '1')
                break;
            j++;
        }
        if (map[i][j] == '\0')
        {
            printf("map error at %d,%d\n", i, j);
            ERROR(INVALID_MAP);
            exit(1);
        }
        i++;
    }
}

int parse_file(int fd, t_file *file)
{
    parse_texture(fd, file);
    //map_reader(fd, file);
    // printf("|NO:%s|\n|SO:%s|\n|EA:%s|\n|WE:%s|\n", file->north, file->south, file->east, file->west);
    // printf("|F:%d,%d,%d|\n|C:%d,%d,%d|\n", file->floor.r, file->floor.g, file->floor.b, file->ceiling.r, file->ceiling.g, file->ceiling.b);
    // printf("line count: %d\n", file->line_count);
    // for (int i = 0; i < file->map_len; i++)
    // {
    //     printf("MAP: %s", file->map[i]);
    // }
    map_checker(file->map);
    map_validator(file->map);
    recheck_map(file->map);
    return (1);
}

void   first_init_colors(t_file *file)
{
    file->floor.r = 0;
    file->floor.g = 0;
    file->floor.b = 0;
    file->ceiling.r = 0;
    file->ceiling.g = 0;
    file->ceiling.b = 0;
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
    file->line_count = 0;
    file->map_len = 0;
    file->map = malloc(sizeof(char *) * 100);
    if (parse_file(fd, file))
        return (NULL);
    return file;
}