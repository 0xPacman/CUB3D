/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:12:32 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/13 16:37:42 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void draw_rays(t_engine *engine) {
    (void)engine;
}

void draw_horizontal_line(t_image *img, int x1, int x2, int y, int color) {
    int i;
    int x_start = fmin(x1, x2);
    int x_end = fmax(x1, x2);

    for (i = x_start; i <= x_end; i++) {
        put_pixel(img, i, y, color);
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
    engine->player.health = 60;
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
    draw_horizontal_line(&engine->img, 0, health_width * engine->player.health / 100, health_offset + health_height / 2, health_color);

    // Draw face image
    int face_width = bar_width / 4;
    int face_height = bar_height;
    int face_offset = bar_offset;
    int face_color = 0xFF0000; // Red for now
    int face_center_x = bar_width / 2 - face_width / 2; // Center the face image
    for (i = 0; i < face_height; i++) {
        for (j = 0; j < face_width; j++) {
            // TODO: Replace this with actual face image
            put_pixel(&engine->img, j + face_center_x, i + face_offset, face_color); // Draw red square for now
        }
    }

    // Draw ammo counter
    int ammo_width = bar_width / 8;
    int ammo_offset = bar_offset + bar_height / 4;
    int ammo_color = 0xFFFFFF; // White for now
    int ammo_center_x = ammo_width * 3 - ammo_width / 2; // Center the ammo counter
    char ammo_text[16];
    snprintf(ammo_text, sizeof(ammo_text), "AMMO: %d", engine->player.ammo);
    draw_text(engine, ammo_text, ammo_center_x, ammo_offset, ammo_color);

    
    // Draw separator lines
    int separator_width = 2; // Set separator width to 1 pixel
    int separator_color = 0xFFFFFF; // White for now
    int separator_offset = bar_offset;
    draw_horizontal_line(&engine->img, health_width, health_width + separator_width, separator_offset, separator_color);
    draw_horizontal_line(&engine->img, bar_width / 2 - separator_width / 2, bar_width / 2 + separator_width / 2, separator_offset, separator_color);
    draw_horizontal_line(&engine->img, ammo_width * 3, ammo_width * 3 + separator_width, separator_offset, separator_color);
    
    // Draw health and ammo labels
    int label_offset = bar_offset - 20;
    int health_label_x = 20;
    int ammo_label_x = bar_width - 70;
    // health with green color
    
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
    mlx_string_put(engine->mlx, engine->win, 20, label_offset, 0x00FF00, "HEALTH");
    mlx_string_put(engine->mlx, engine->win, 20, label_offset, 0x00FF00, "AMMO");
    return (0);
}

void    game_loop(t_engine *engine) {
    // init the image
    engine->img.img = mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(engine->img.img, &engine->img.bits_per_pixel, &engine->img.line_length, &engine->img.endian);
    
    // start the game loop
    mlx_loop_hook(engine->mlx, &frame, engine);
}