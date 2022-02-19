/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:22:57 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/19 17:15:26 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	size_of_words(char const *s, char c)
{
	int	size;
	int	i;
	int	j;

	j = 0;
	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (j == 0)
				size++;
			j++;
		}
		else
			j = 0;
		i++;
	}
	return (size);
}

static void	free_table(char **p, int index)
{
	while (index > 0)
	{
		free(p[index - 1]);
		index--;
	}
	free(p);
}

static int	fill(char const *s, char c, char **p, int size)
{
	int	start;
	int	index;
	int	i;

	start = 0;
	index = 0;
	i = 0;
	while (index < size)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		p[index] = ft_substr(s, start, i - start);
		if (!p[index])
		{
			free_table(p, index);
			return (0);
		}
		index++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		size;

	if (!s)
		return (0);
	size = size_of_words(s, c);
	p = (char **)malloc(sizeof(char *) * (size + 1));
	if (!p)
		throw_error(0);
	if (!fill(s, c, p, size))
		throw_error(0);
	p[size] = 0;
	return (p);
}
