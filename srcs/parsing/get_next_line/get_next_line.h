/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <ahjadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:01:05 by roudouch          #+#    #+#             */
/*   Updated: 2023/02/03 15:43:39 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../../../libft/libft.h"

# define BUFFER_SIZE 42

char			*get_next_line(int fd);
char			*ft_strjoin2(char *s1, char const *s2);
int				ft_index(const char *s, char c);

#endif