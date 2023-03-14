/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:12:32 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/13 18:09:21 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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


void draw_text(t_engine *engine, char *text, int x, int y, int color) {
    int i, j, offset;

    for (i = 0; i < CHAR_HEIGHT; i++) {
        for (j = 0; j < CHAR_WIDTH; j++) {
            offset = (y + i) * engine->img.line_length + (x + j) * (engine->img.bits_per_pixel / 8);
            if (text[i * CHAR_WIDTH + j] == 'X') {
                put_pixel(&engine->img, x + j, y + i, color);
            }
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
    bar_height = SCREEN_HEIGHT / 7;
    bar_offset = SCREEN_HEIGHT - bar_height;

    // Draw background of status bar
    for (i = 0; i < bar_height; i++) {
        for (j = 0; j < bar_width; j++) {
            put_pixel(&engine->img, j, i + bar_offset, 0x333333);
        }
    }

    // Draw health bar
    int health_width = bar_width / 4;
    int health_height = bar_height / 2;
    int health_offset = bar_offset + bar_height / 4;
    int health_color = (engine->player.health > 50) ? 0x00FF00 : 0xFF0000; // Green if health > 50, red otherwise
    draw_thick_horizontal_line(&engine->img, 0, health_width * engine->player.health / 100, health_offset + health_height / 2, 20, health_color);

    // Draw face image
    int face_width = bar_width / 4;
    int face_height = bar_height;
    int face_offset = bar_offset;
    int face_color = 0x616161;
    int face_center_x = bar_width / 2 - face_width / 2; // Center the face image
    for (i = 0; i < face_height; i++) {
        for (j = 0; j < face_width; j++) {
            // TODO: Replace this with actual face image
            put_pixel(&engine->img, j + face_center_x, i + face_offset, face_color); // Draw red square for now
            //draw face, face located at textures/face/face.xpm
            // for (int i = 0; i < 24; i++) {
            //     for (int j = 0; j < 24; j++) {
            //         put_pixel(&engine->img, j + face_center_x, i + face_offset, get_color(&engine->texture[0], j, i));
            //     }
            // }
        }
    }

}



int frame(t_engine *engine) {
    // clear the window
    mlx_clear_window(engine->mlx, engine->win);
    
    // check for controls
    check_controls(engine);

    // draw rayes on the map from the player
    start_casting(engine);

	/// draw mini map
    draw_map(engine);

    // draw the player 
    draw_square(engine, engine->player.pos.x * 10, engine->player.pos.y * 10, 10, 0xFF0000);

    // draw status bar
    draw_status_bar(engine);
    
    // put the image to the window
    mlx_put_image_to_window(engine->mlx, engine->win, engine->img.img, 0, 0);
    mlx_string_put(engine->mlx, engine->win, 1200, 660, 0xFFD700, "30");
    mlx_string_put(engine->mlx, engine->win, 20, 690, 0x00FF00, "HEALTH");
    mlx_string_put(engine->mlx, engine->win, 1220, 690, 0x00FF00, "AMMO");
    return (0);
}

void    game_loop(t_engine *engine) {
    // init the image
    engine->img.img = mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(engine->img.img, &engine->img.bits_per_pixel, &engine->img.line_length, &engine->img.endian);
    
    // start the game loop
    mlx_loop_hook(engine->mlx, &frame, engine);
}