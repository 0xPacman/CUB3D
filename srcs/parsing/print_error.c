/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:49:27 by ahjadani          #+#    #+#             */
/*   Updated: 2023/02/03 10:37:00 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void   print_error(int error)
{
    if (error == 0)
        ft_putstr_fd("Error: Invalid arguments\n", 2);
    else if (error == 1)
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
    else if (error == 2)
        ft_putstr_fd("Error: Failed to read the file\n", 2);
    else if (error == 3)
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
    else if (error == 4)
        ft_putstr_fd("Error: Parsing the texture failed\n", 2);
    else if (error == 5)
        ft_putstr_fd("Error: Parsing the map failed\n", 2);
    else if (error == 6)
        ft_putstr_fd("Error: The map is not valid\n", 2);
    else if (error == 7)
        ft_putstr_fd("Error: The player is not valid\n", 2);
    else
        ft_putstr_fd("Error: Unknown error\n", 2);
}
        