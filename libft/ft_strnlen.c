/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:56:43 by ahjadani          #+#    #+#             */
/*   Updated: 2021/11/12 00:51:04 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (i < maxlen)
	{
		if (!s[i])
			break ;
		len++;
		i++;
	}
	return (len);
}
