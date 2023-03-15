/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:26:55 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/15 13:15:52 by ahjadani         ###   ########.fr       */
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

void load_faces(t_engine *engine, t_file *file)
{
    load_texture(engine, file->face[0], &engine->face[0]);
    load_texture(engine, file->face[1], &engine->face[1]);
    load_texture(engine, file->face[2], &engine->face[2]);
    load_texture(engine, file->face[3], &engine->face[3]);
    load_texture(engine, file->face[4], &engine->face[4]);
}

void load_guns(t_engine *engine, t_file *file)
{
    load_texture(engine, file->gun[0], &engine->gun[0]);
    load_texture(engine, file->gun[1], &engine->gun[1]);
    load_texture(engine, file->gun[2], &engine->gun[2]);
    load_texture(engine, file->gun[3], &engine->gun[3]);
}

void load_gps(t_engine *engine, t_file *file)
{
    load_texture(engine, file->gps[0], &engine->gps[0]);
}

void load_door(t_engine *engine, t_file *file)
{
    load_texture(engine, file->door[0], &engine->door[0]);
    load_texture(engine, file->open_door[0], &engine->open_door[0]);
}

void apply_texture(t_engine *engine, t_file *file)
{
    load_texture(engine, file->west, &engine->texture[WEST]);
    load_texture(engine, file->east, &engine->texture[EAST]);
    load_texture(engine, file->north, &engine->texture[NORTH]);
    load_texture(engine, file->south, &engine->texture[SOUTH]);
    load_faces(engine, file);
    load_guns(engine, file);
    load_gps(engine, file);
    load_door(engine, file);
    
}

void init_texture(t_engine *engine, t_file *file)
{
    t_texture *texture;
    t_texture *face;
    t_texture *gun;
    t_texture *gps;
    t_texture *door;
    t_texture *open_door;
    door = malloc(sizeof(t_texture) * 1);
    face = malloc(sizeof(t_texture) * 5);
    texture = malloc(sizeof(t_texture) * 4);
    gun = malloc(sizeof(t_texture) * 4);
    gps = malloc(sizeof(t_texture) * 1);
    open_door = malloc(sizeof(t_texture) * 1);
    if (!texture || !face || !gun || !gps || !door)
    {
        ERROR(INIT_TEXTURE);
        exit(EXIT_FAILURE);
    }
    engine->texture = texture;
    engine->face = face;
    engine->gun = gun;
    engine->gps = gps;
    engine->door = door;
    engine->open_door = open_door;
    apply_texture(engine, file);
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

void    init_player_dir(char dir, t_engine *engine)
{
    if (dir == 'N') 
    {
        engine->player.dir.x = -1;
        engine->player.dir.y = 0;
        engine->player.plane.x = 0;
        engine->player.plane.y = 0.66;
    }
    else if (dir == 'S') 
    {
        engine->player.dir.x = 1;
        engine->player.dir.y = 0;
        engine->player.plane.x = 0;
        engine->player.plane.y = -0.66;
    }
    else if (dir == 'E') 
    {
        engine->player.dir.x = 0;
        engine->player.dir.y = 1;
        engine->player.plane.x = 0.66;
        engine->player.plane.y = 0;
    }
    else if (dir == 'W') 
    {
        engine->player.dir.x = 0;
        engine->player.dir.y = -1;
        engine->player.plane.x = -0.66;
        engine->player.plane.y = 0;
    }
}

void start_engine(t_file *file)
{
    t_engine *engine;

    engine = malloc(sizeof(t_engine));
    if (engine && init_engine(engine))
    {
        engine->player.pos.x = file->p_pos.x;
        engine->player.pos.y = file->p_pos.y;
        init_player_dir(file->p_dir, engine);
        engine->player.move_speed = 0.06;
        engine->player.rot_speed = 0.03;
        engine->map = file->map;
        engine->which_face_to_draw = 0;
        engine->which_gun_to_draw = 0;
        engine->floor = file->floor;
        engine->ceiling = file->ceiling;
        engine->player.health = 100;
        engine->player.ammo = 100;
        int i = 0;
        while (engine->map[i])
        {
            engine->map[i][ft_strlen(engine->map[i]) - 1] = '\0';
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