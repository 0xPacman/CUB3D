/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:26:55 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/13 16:38:37 by ahjadani         ###   ########.fr       */
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