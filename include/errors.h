/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:26:47 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/04 13:00:04 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// define the error messages as macros
# define ALLOCATE_ERROR "Error: Memory allocation failed."
# define INIT_ENGINE "Error: Failed to initialize engine!\n"
# define INVALID_ARGS "Error: Invalid arguments\n"
# define READ_FILE "Error: Failed to read the file\n"
# define OPEN_FILE "Error: Failed to open the file\n"
# define PARSE_TEXTURE "Error: Parsing the texture failed\n"
# define PARSE_MAP "Error: Parsing the map failed\n"
# define MAP_VALID "Error: The map is not valid\n"
# define PLAYER_VALID "Error: The player is not valid\n"
# define UNKNOWN_ERROR "Error: Unknown error\n"
# define INVALID_RGB "Error: Invalid RGB\n"
# define INVALID_TEXTURE "Error: Invalid texture\n"


// define the print error function as a macro
# define ERROR(x) ft_putstr_fd(x, 2)

#endif