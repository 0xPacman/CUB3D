/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahjadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 09:34:29 by ahjadani          #+#    #+#             */
/*   Updated: 2021/11/11 22:55:41 by ahjadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_skip(char const *s, int pos, char c)
{
	while (s[pos] == c)
		pos++;
	return (pos);
}

static char	**ft_clean(char **strs, int pos)
{
	while (--pos >= 0)
		free(strs[pos]);
	free(strs);
	return (NULL);
}

static int	ft_words_counter(char const *s, char c)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**strs;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	strs = (char **)malloc(sizeof(char *) * ft_words_counter(s, c) + 1);
	if (!strs)
		return (NULL);
	while (s[i])
	{
		i = ft_skip(s, i, c);
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
			strs[k++] = ft_strndup(&s[j], i - j);
		if (!strs[k - 1])
			return (ft_clean(strs, k - 1));
	}
	strs[k] = NULL;
	return (strs);
}
