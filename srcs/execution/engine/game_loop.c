/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:12:32 by roudouch          #+#    #+#             */
/*   Updated: 2023/03/16 15:09:10 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	map_len_y(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	map_len_x(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		i++;
	}
	return (j);
}

int	frame(t_engine *engine)
{
	mlx_clear_window(engine->mlx, engine->win);
	check_controls(engine);
	start_casting(engine);
	if (map_len_x(engine->map) > 5 && map_len_y(engine->map) > 5)
		draw_map(engine, 7);
	draw_status_bar(engine);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img.img, 0, 0);
	mlx_string_put(engine->mlx, engine->win, 1200, 660, 0xFFD700,
		ft_itoa(engine->player.ammo));
	mlx_string_put(engine->mlx, engine->win, 20, 690, 0x00FF00, "HEALTH");
	mlx_string_put(engine->mlx, engine->win, 1220, 690, 0x00FF00, "AMMO");
	mlx_put_image_to_window(engine->mlx, engine->win, engine->gps[0].img, 4, 5);
	draw_face(engine, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100);
	if (engine->can_open_door)
		mlx_put_image_to_window(engine->mlx, engine->win, engine->open_door
		[0].img, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50);
	else if (engine->can_close_door)
		mlx_put_image_to_window(engine->mlx, engine->win, engine->close_door
		[0].img, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50);
	return (0);
}

void	game_loop(t_engine *engine)
{
	engine->img.img = mlx_new_image(engine->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	engine->img.addr = mlx_get_data_addr(
			engine->img.img,
			&engine->img.bits_per_pixel,
			&engine->img.line_length,
			&engine->img.endian
			);
	mlx_loop_hook(engine->mlx, &frame, engine);
}
