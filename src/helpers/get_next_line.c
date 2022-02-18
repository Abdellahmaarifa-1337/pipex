/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:44:57 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/18 19:42:43 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_line(char **s)
{
	char	*temp;
	int		j;
	char	*t_s;

	j = get_nl(*s);
	if (j >= 0)
	{
		temp = ft_substr(*s, 0, j + 1);
		t_s = ft_strdup(*s + j + 1);
		free(*s);
		*s = t_s;
		return (temp);
	}
	temp = ft_strdup(*s);
	s[0][0] = '\0';
	return (temp);
}

void	read_line(int fd, char **buf, char **s, int buffer_size)
{
	int	j;

	while (1)
	{
		j = read(fd, *buf, buffer_size);
		if (j <= 0)
			break ;
		buf[0][j] = '\0';
		*s = ft_strjoin(*s, *buf);
		if (get_nl(*buf) >= 0)
			break ;
	}
}

char	*get_next_line(int fd, int buffer_size)
{
	char		*buf;
	static char	*s;

	if (fd < 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (buffer_size + 1));
	if (!buf)
		return (0);
	if (!s)
		s = ft_strdup("");
	read_line(fd, &buf, &s, buffer_size);
	free(buf);
	if (s && s[0])
		return (get_line(&s));
	if (s)
		free(s);
	s = NULL;
	return (0);
}
