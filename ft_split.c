/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:52:37 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/18 12:31:23 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_countwords(const char *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	if (s[i] == 0)
		return (0);
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == 0)))
			w++;
		i++;
	}
	return (w);
}

static char	**ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	*ft_createlines(const char *s, char c)
{
	int		i;
	char	*line;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	char			**tab;

	i = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			tab[i] = ft_createlines(s, c);
			if (!tab[i])
				return (ft_freetab(tab));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

// #include <stdio.h>
// int	main(void)
// {
// 	// ft_split("hello!", ' ');
// 	char **tab;
// 	int i = 0;

// 	tab = ft_split("hello!", ' ');
// 	while (tab[i])
// 	{
// 		printf("%s", tab[i]);
// 		i++;
// 	}
// 	printf("%s", tab[i]);
// 	ft_freetab(tab);
// 	// char *test = NULL;
// 	// printf("%d", ft_countwords(test, ' '));
// }