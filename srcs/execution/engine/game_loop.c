/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:12:32 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/15 15:46:44 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"
#include <time.h>
void draw_rays(t_engine *engine) {
    (void)engine;
}

void draw_thick_horizontal_line(t_image *img, int x1, int x2, int y, int thickness, int color) {
    int i, j;
    int x_start = fmin(x1, x2);
    int x_end = fmax(x1, x2);
    int y_start = y - (thickness - 1) / 2;
    int y_end = y + thickness / 2;

    for (j = y_start; j <= y_end; j++) {
        for (i = x_start; i <= x_end; i++) {
            put_pixel(img, i, j, color);
        }
    }
}


void draw_face_image(t_engine *engine, int x, int y, int width, int height) {
    // Load the face texture
    t_texture *face_texture = engine->face;

    // Calculate the aspect ratio of the face texture
    float texture_aspect_ratio = (float)face_texture->width / (float)face_texture->height;

    // Calculate the aspect ratio of the target square
    float target_aspect_ratio = (float)width / (float)height;

    // Calculate the scale factor based on the aspect ratios
    float scale_factor;
    if (texture_aspect_ratio > target_aspect_ratio) {
        // If the texture aspect ratio is wider than the target square, scale by the height
        scale_factor = (float)height / (float)face_texture->height;
    } else {
        // Otherwise, scale by the width
        scale_factor = (float)width / (float)face_texture->width;
    }

    // Calculate the new dimensions of the face texture based on the scale factor
    int new_width = face_texture->width * scale_factor;
    int new_height = face_texture->height * scale_factor;

    // Calculate the position of the top-left corner of the face texture within the square
    int offset_x = x + (width - new_width) / 2;
    int offset_y = y + (height - new_height) / 2;

    // Draw the scaled face texture within the square
    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            int texture_x = j / scale_factor;
            int texture_y = i / scale_factor;

            unsigned int color = get_color(face_texture, texture_x, texture_y);

            put_pixel(&engine->img, offset_x + j, offset_y + i, color);
        }
    }
}

void draw_status_bar(t_engine *engine) {
    int bar_width;
    int bar_height;
    int bar_offset;
    int i, j;
    engine->player.health = 99;
    // Calculate dimensions and position of status bar
    bar_width = SCREEN_WIDTH;
    bar_height = engine->player.health;
    bar_offset = SCREEN_HEIGHT - bar_height;

    // Draw background of status bar
    for (i = 0; i < bar_height; i++) {
        for (j = 0; j < bar_width; j++) {
            put_pixel(&engine->img, j, i + bar_offset, 0x0D4D4D);
        }
    }

    // Draw health bar
    int health_width = bar_width / 4;
    int health_height = bar_height / 2;
    int health_offset = bar_offset + bar_height / 4;
    int health_color = (engine->player.health > 50) ? 0x00FF00 : 0xFF0000; // Green if health > 50, red otherwise
    draw_thick_horizontal_line(&engine->img, 0, health_width * engine->player.health / 100, health_offset + health_height / 2, 20, health_color);
    
}


void draw_face(t_engine *engine, int x, int y) {
    if (engine->controls.left) {
        mlx_put_image_to_window(engine->mlx, engine->win,  engine->gun[0].img, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 200);
        mlx_put_image_to_window(engine->mlx, engine->win,  engine->face[2].img, x, y);
    } else if (engine->controls.right) {
        mlx_put_image_to_window(engine->mlx, engine->win,  engine->face[3].img, x, y);
        mlx_put_image_to_window(engine->mlx, engine->win,  engine->gun[0].img, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 200);
    } else if (engine->controls.space && engine->player.ammo > 0) {
        mlx_put_image_to_window(engine->mlx, engine->win,  engine->gun[engine->which_gun_to_draw % 4].img, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 200);
        engine->player.ammo--;
        engine->which_gun_to_draw++;
        mlx_put_image_to_window(engine->mlx, engine->win,  engine->face[4].img, x, y);
    } else if(engine->controls.r) {
        engine->player.ammo = 100;
    } else {
        mlx_put_image_to_window(engine->mlx, engine->win,  engine->gun[0].img, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 200);
        if (engine->which_face_to_draw < 30) {
            mlx_put_image_to_window(engine->mlx, engine->win,  engine->face[0].img, x, y);
            engine->which_face_to_draw++;
        } else if (engine->which_face_to_draw < 60) {
            mlx_put_image_to_window(engine->mlx, engine->win,  engine->face[1].img, x, y);
            engine->which_face_to_draw++;
        } else {
            engine->which_face_to_draw = 0;
            mlx_put_image_to_window(engine->mlx, engine->win,  engine->face[1].img, x, y);
        }
    }
}

int map_len_y(char **map)
{
    int i;

    i = 0;
    while(map[i])
        i++;
    return (i);
}

int map_len_x(char **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
            j++;
        i++;
    }
    return (j);
}

int frame(t_engine *engine) {
    // clear the window
    mlx_clear_window(engine->mlx, engine->win);
    
    // check for controls
    check_controls(engine);

    // draw rayes on the map from the player
    start_casting(engine);

	// draw mini map
    if (map_len_x(engine->map) > 5 && map_len_y(engine->map) > 5)
        draw_map(engine, 7);
    
    
    //draw_map(engine, 7);

    

    // draw status bar
    draw_status_bar(engine);
    
    // put the image to the window
    mlx_put_image_to_window(engine->mlx, engine->win, engine->img.img, 0, 0);
    mlx_string_put(engine->mlx, engine->win, 1200, 660, 0xFFD700, ft_itoa(engine->player.ammo));
    mlx_string_put(engine->mlx, engine->win, 20, 690, 0x00FF00, "HEALTH");
    mlx_string_put(engine->mlx, engine->win, 1220, 690, 0x00FF00, "AMMO");
    
    mlx_put_image_to_window(engine->mlx, engine->win, engine->gps[0].img, 4, 5);
    draw_face(engine, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100);
    
    if (engine->can_open_door) {
        mlx_put_image_to_window(engine->mlx, engine->win, engine->open_door[0].img, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50);
    } else if (engine->can_close_door) {
        mlx_put_image_to_window(engine->mlx, engine->win, engine->close_door[0].img, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50);
    }
    
    return (0);
}

void    game_loop(t_engine *engine) {
    // init the image
    engine->img.img = mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(engine->img.img, &engine->img.bits_per_pixel, &engine->img.line_length, &engine->img.endian);
    
    // start the game loop
    mlx_loop_hook(engine->mlx, &frame, engine);
}