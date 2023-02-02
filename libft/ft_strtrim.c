/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:41:16 by ahjadani          #+#    #+#             */
/*   Updated: 2021/11/14 18:09:00 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	ssize_t	i;
	ssize_t	j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_strchr((char *)set, s1[i]))
		i++;
	while (ft_strrchr((char *)set, s1[j]))
		j--;
	if (j < i)
		return (ft_strdup(""));
	str = malloc(j - i + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, j - i + 2);
	return (str);
}
