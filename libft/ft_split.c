/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:46:09 by medel-ca          #+#    #+#             */
/*   Updated: 2025/04/17 17:51:58 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(const char *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

static void	ft_free_all(char **splits, int last)
{
	while (--last >= 0)
		free(splits[last]);
	free(splits);
}

static int	ft_fill_split(char **splits, const char *s, char c)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		if (!s[start])
			break ;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		splits[i] = ft_substr(s, start, end - start);
		if (!splits[i])
		{
			ft_free_all(splits, i);
			return (0);
		}
		i++;
		start = end;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	int		words;

	if (!s)
		return (NULL);
	words = ft_wordcount(s, c);
	splits = ft_calloc((words + 1), sizeof(char *));
	if (!splits)
		return (NULL);
	if (!ft_fill_split(splits, s, c))
		return (NULL);
	return (splits);
}
