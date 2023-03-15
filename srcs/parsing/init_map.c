/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:45:17 by ahjadani          #+#    #+#             */
/*   Updated: 2023/03/15 12:57:18 by ahjadani         ###   ########.fr       */
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
    if (file->floor.r > 255 || file->floor.r < 0 || file->floor.g > 255 
    || file->floor.g < 0 || file->floor.b > 255 || file->floor.b < 0)
    {
        ERROR(INVALID_RGB);
        exit(1);
    }
    if (file->ceiling.r > 255 || file->ceiling.r < 0 || file->ceiling.g > 255 
    || file->ceiling.g < 0 || file->ceiling.b > 255 || file->ceiling.b < 0)
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

int check_for_one(char *line, t_file *file)
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

void map_reader(char *line, t_file *file)
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
            line = ft_strdup("[]");
        }
        split_line = ft_split(line + i, ' ');
        if (line[i] == '1' && !check_init(file))
        {
            ERROR(INVALID_MAP);
            exit(1);
        }
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
                    //printf("map error at %d,%d\n", i, j);
                    ERROR(INVALID_MAP);
                    exit(1);
                }
            }
            j++;
        }
        i++;
    }
}



int map_checker(char **map, t_file *file)
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
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W' )
            {
                file->p_dir = map[i][j];
                file->p_pos.x = j;
                file->p_pos.y = i;
            }
                
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W' 
            || map[i][j] == '0' || map[i][j] == '1' || map[i][j] == ' ' || map[i][j] == '\n'
            || map[i][j] == 'D')
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

int check_1_line(char *line)
{

    // if the first line contains a only 1's and whitespaces return 1
    int i = 0;
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

int check_mid_lines(char *line)
{
    // check if the line contains 1 at the beginning and at the end and ignore whitespaces
    int i = 0;
    int j = ft_strlen(line) - 1;
    while (ft_isspace(line[i]))
        i++;
    while (ft_isspace(line[j]))
        j--;
    if (line[i] == '1' && line[j] == '1')
        return (1);
    return (0);

}

void recheck_map(char **map)
{
    size_t i = 0;
    size_t j = 0;
    
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (i == 0)
            {
                if (!check_1_line(map[i]))
                {
                    ERROR(INVALID_MAP);
                    exit(1);
                }
            }
            else if (i == ft_strlen(map[i]))
            {
                if (!check_1_line(map[i]))
                {
                    ERROR(INVALID_MAP);
                    exit(1);
                }
            }
            else if (j == 0)
            {
                if (!check_mid_lines(map[i]))
                {
                    ERROR(INVALID_MAP);
                    exit(1);
                }
            }
            else if (j == ft_strlen(map[i]))
            {
                if (!check_mid_lines(map[i]))
                {
                    ERROR(INVALID_MAP);
                    exit(1);
                }
            }
            j++;
        }
        i++;
    }
    
}



void parse_faces(t_file *file)
{
    file->face = malloc(sizeof(t_texture) * 5);
    if (!file->face)
        ERROR(ALLOCATE_ERROR);
    file->face[0] = ft_strdup("textures/face/loop_face.xpm");
    file->face[1] = ft_strdup("textures/face/loop_face1.xpm");
    file->face[2] = ft_strdup("textures/face/left_face.xpm");
    file->face[3] = ft_strdup("textures/face/right_face.xpm");
    file->face[4] = ft_strdup("textures/face/shot.xpm");
}

void parse_gun(t_file *file)
{
    file->gun = malloc(sizeof(t_texture) * 4);
    if (!file->gun)
        ERROR(ALLOCATE_ERROR);
    file->gun[0] = ft_strdup("textures/gun/gun.xpm");
    file->gun[1] = ft_strdup("textures/gun/gun1.xpm");
    file->gun[2] = ft_strdup("textures/gun/gun2.xpm");
    file->gun[3] = ft_strdup("textures/gun/gun3.xpm");
}

void parse_gps(t_file *file)
{
    file->gps = malloc(sizeof(t_texture) * 1);
    if (!file->gps)
        ERROR(ALLOCATE_ERROR);
    file->gps[0] = ft_strdup("textures/gps.xpm");

}

void parse_door(t_file *file)
{
    file->door = malloc(sizeof(t_texture) * 1);
    if (!file->door)
        ERROR(ALLOCATE_ERROR);
    file->door[0] = ft_strdup("textures/door.xpm");
}

int parse_file(int fd, t_file *file)
{
    parse_texture(fd, file);
    map_checker(file->map, file);
    map_validator(file->map);
    recheck_map(file->map);
    parse_faces(file);
    parse_gun(file);
    parse_gps(file);
    parse_door(file);
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
    file->flag = 0;
    file->map = malloc(sizeof(char *) * 10000);
    if (!parse_file(fd, file))
        return (NULL);
    return file;
}