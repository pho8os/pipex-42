/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:55:28 by absaid            #+#    #+#             */
/*   Updated: 2023/01/16 18:37:09 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	cw(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			count++;
	return (count);
}

static void	free_all(char **str, int l)
{
	while (l)
	{
		free(str[l]);
		l--;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;
	int		j;
	int		l;

	i = 0;
	l = -1;
	if (!s)
		return (NULL);
	p = (char **)gc(sizeof (char *) * (cw((char *)s, c) + 1), 1);
	if (!p)
		return (NULL);
	while (++l < cw((char *)s, c))
	{	
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		p[l] = ft_substr(s, j, i - j);
		if (!p[l])
			return (free_all(p, l), NULL);
	}
	return (p[l] = NULL, p);
}
