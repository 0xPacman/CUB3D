/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:26:55 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/13 10:20:53 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void load_texture(t_engine *engine, char *path, t_texture *texture)
{
    texture->img = mlx_xpm_file_to_image(engine->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
    {
        ERROR(INVALID_TEXTURE);
        exit(EXIT_FAILURE);
    }
    texture->data = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_len, &texture->endian);
}

// to do : apply_texture function
void apply_texture(t_engine *engine, t_file *file)
{
    // to debug
    //  printf("\n|%s|\n|%s|\n|%s|\n|%s|\n", file->north, file->south, file->east, file->west);
    load_texture(engine, file->west, &engine->texture[WEST]);
    load_texture(engine, file->east, &engine->texture[EAST]);
    load_texture(engine, file->north, &engine->texture[NORTH]);
    load_texture(engine, file->south, &engine->texture[SOUTH]);
}

void init_texture(t_engine *engine, t_file *file)
{
    t_texture *texture;

    texture = malloc(sizeof(t_texture) * 4);
    if (!texture)
    {
        ERROR(INIT_TEXTURE);
        exit(EXIT_FAILURE);
    }
    engine->texture = texture;
    apply_texture(engine, file);
    // printf("%s\n",file->north);
}

bool init_engine(t_engine *engine)
{
    engine->mlx = NULL;
    engine->win = NULL;
    engine->mlx = mlx_init();
    if (engine->mlx)
    {
        engine->win = mlx_new_window(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Wolf4D");
        if (engine->win)
            return (true);
    }
    if (engine->win)
        mlx_destroy_window(engine->mlx, engine->win);
    return (false);
}

char **create_clean_map(char **map)
{
    int i;
    int j;
    char **clean_map;

    i = 0;
    while (map[i])
        i++;
    clean_map = malloc(sizeof(char *) * (i + 1));
    if (!clean_map)
        return (NULL);
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
            j++;
        clean_map[i] = malloc(sizeof(char) * (j + 1));
        if (!clean_map[i])
            return (NULL);
        j = 0;
        while (map[i][j])
        {
            clean_map[i][j] = map[i][j];
            j++;
        }
        clean_map[i][j] = '\0';
        i++;
    }
    clean_map[i] = NULL;
    return (clean_map);
}

void start_engine(t_file *file)
{
    t_engine *engine;

    engine = malloc(sizeof(t_engine));
    if (engine && init_engine(engine))
    {

        // for testing purposes
        engine->player.pos.x = 3;
        engine->player.pos.y = 3;
        engine->player.dir.x = cos(PI); //-1
        engine->player.dir.y = sin(PI); // 0
        engine->player.plane.x = 0;
        engine->player.plane.y = 0.66;
        engine->player.move_speed = 0.06;
        engine->player.rot_speed = 0.03;

        engine->map = create_clean_map(file->map);

        int i = 0;
        while (engine->map[i])
        {
            engine->map[i][ft_strlen(engine->map[i]) - 1] = '\0';
            printf("%s\n", engine->map[i]);
            i++;
        }

        init_texture(engine, file);
        init_controls(engine);
        game_loop(engine);
        mlx_loop(engine->mlx);
    }
    else
    {
        free(engine);
        ERROR(INIT_ENGINE);
        exit(EXIT_FAILURE);
    }
}