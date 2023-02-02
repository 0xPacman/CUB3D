/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:56:13 by ahjadani          #+#    #+#             */
/*   Updated: 2021/11/11 22:58:38 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n && (*(unsigned char *)s != (unsigned char)c))
	{
		s = (unsigned char *) s + 1;
		n--;
	}
	if (n)
		return ((void *)s);
	else
		return (NULL);
}
