/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:50:05 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/13 10:22:00 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void init_vars(t_engine *engine, int x) {
    // calculate ray position and direction
    engine->ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space
    // calculate ray position and direction
    engine->ray.dir.x = engine->player.dir.x + engine->player.plane.x * engine->ray.camera_x;
    engine->ray.dir.y = engine->player.dir.y + engine->player.plane.y * engine->ray.camera_x;
    // which box of the map we're in
    engine->ray.map.x = (int)engine->player.pos.x;
    engine->ray.map.y = (int)engine->player.pos.y;
    // length of ray from current position to next x or y-side
    engine->ray.delta_dist.x = fabs(1 / engine->ray.dir.x);
    engine->ray.delta_dist.y = fabs(1 / engine->ray.dir.y);
    engine->ray.hit = 0; // was there a wall hit?
}

void init_dda(t_engine *engine) {
    // calculate step and initial sideDist
    if (engine->ray.dir.x < 0) {
        engine->ray.step.x = -1;
        engine->ray.side_dist.x = (engine->player.pos.x - engine->ray.map.x) * engine->ray.delta_dist.x;
    } else {
        engine->ray.step.x = 1;
        engine->ray.side_dist.x = (engine->ray.map.x + 1.0 - engine->player.pos.x) * engine->ray.delta_dist.x;
    }
    if (engine->ray.dir.y < 0) {
        engine->ray.step.y = -1;
        engine->ray.side_dist.y = (engine->player.pos.y - engine->ray.map.y) * engine->ray.delta_dist.y;
    } else {
        engine->ray.step.y = 1;
        engine->ray.side_dist.y = (engine->ray.map.y + 1.0 - engine->player.pos.y) * engine->ray.delta_dist.y;
    }
}

void perform_dda(t_engine *engine) {
    // perform DDA
    while (engine->ray.hit == 0) {
        // jump to next map square, OR in x-direction, OR in y-direction
        if (engine->ray.side_dist.x < engine->ray.side_dist.y) {
            engine->ray.side_dist.x += engine->ray.delta_dist.x;
            engine->ray.map.x += engine->ray.step.x;
            engine->ray.side = 0;
        } else {
            engine->ray.side_dist.y += engine->ray.delta_dist.y;
            engine->ray.map.y += engine->ray.step.y;
            engine->ray.side = 1;
        }
        // Check if ray has hit a wall
        if (engine->map[(int)engine->ray.map.y][(int)engine->ray.map.x] == '1')
            engine->ray.hit = 1;
    }
}

void calculate_wall_dist(t_engine *engine) {
    // Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
    if (engine->ray.side == 0)
        engine->ray.perp_wall_dist = (engine->ray.side_dist.x - engine->ray.delta_dist.x);
    else
        engine->ray.perp_wall_dist = (engine->ray.side_dist.y - engine->ray.delta_dist.y);
}

void calculate_line_height(t_engine *engine) {
    // Calculate height of line to draw on screen
    engine->ray.line_height = (int)(SCREEN_HEIGHT / engine->ray.perp_wall_dist);
    // calculate lowest and highest pixel to fill in current stripe
    engine->ray.draw_start = -engine->ray.line_height / 2 + SCREEN_HEIGHT / 2;
    if (engine->ray.draw_start < 0)
        engine->ray.draw_start = 0;
    engine->ray.draw_end = engine->ray.line_height / 2 + SCREEN_HEIGHT / 2;
    if (engine->ray.draw_end >= SCREEN_HEIGHT)
        engine->ray.draw_end = SCREEN_HEIGHT - 1;
}


int check_side(t_engine *engine) {
    if (engine->ray.side == 0) {
        if (engine->ray.dir.x > 0)
            return (WEST);
        else
            return (EAST);
    } else {
        if (engine->ray.dir.y > 0)
            return (NORTH);
        else
            return (SOUTH);
    }
}

void    calc_tex_x(t_engine *engine, int side) {
    float wall_x; // where exactly the wall was hit
    if (engine->ray.side == 0)
        wall_x = engine->player.pos.y + engine->ray.perp_wall_dist * engine->ray.dir.y;
    else
        wall_x = engine->player.pos.x + engine->ray.perp_wall_dist * engine->ray.dir.x;
    wall_x -= (int)((wall_x));
    // x coordinate on the texture
    engine->tex_pos.x = (int)(wall_x * (float)engine->texture[side].width);
    engine->tex_step = (float)engine->texture[side].height / engine->ray.line_height;
    if (engine->ray.line_height < SCREEN_HEIGHT) {
        engine->tex_range = 0;
    } else 
        engine->tex_range = ((engine->ray.line_height / 2) - SCREEN_HEIGHT / 2) * engine->tex_step;
}

unsigned int    get_color(t_texture *t, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = (y * t->line_len) + (x * (t->bits_per_pixel / 8));
	ptr = t->data + pixel;
    
    return (((((unsigned char)ptr[2]) << 16) + (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0])));
}


void draw_wall(t_engine *engine, int x) {
    int y;
    int side;

    // check which side of the wall we are on
    side = check_side(engine);
    calc_tex_x(engine, side);
    // draw ceiling
    y = 0;
    while (y < engine->ray.draw_start) {
        put_pixel(&engine->img, x, y, 0x03adcb);
        y++;
    }
    
    // draw wall
    y = engine->ray.draw_start;
    while (y < engine->ray.draw_end) {
        
        engine->tex_pos.y = (int)engine->tex_range % (engine->texture[side].height);
        //printf("side: %d\n", side);
        put_pixel(&engine->img, x, y, get_color(&engine->texture[side], engine->tex_pos.x, engine->tex_pos.y));
        
        engine->tex_range += engine->tex_step;
        
        y = y + 1;
    }

    // draw floor
    y = engine->ray.draw_end;
    while (y < SCREEN_HEIGHT) {
        put_pixel(&engine->img, x, y, 0x33bf02);
        y++;
    }
}

void start_casting(t_engine *engine) 
{
    int x;

    x = 0;
    while (x < SCREEN_WIDTH) {
        init_vars(engine, x);
        init_dda(engine);
        perform_dda(engine);
        calculate_wall_dist(engine);
        calculate_line_height(engine);
        draw_wall(engine, x);
        x++;
    }
}