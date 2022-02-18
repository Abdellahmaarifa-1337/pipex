/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_px.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:17:33 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/18 19:40:08 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../pipex.h"

void	init_file(t_px *px, char **av, int ac)
{
	int		here_doc;

	here_doc = !ft_strcmp(av[1], "here_doc");
	if (!here_doc)
	{
		(*px).file[0] = open(av[1], O_RDONLY);
		if ((*px).file[0] == -1)
			perror(0);
		(*px).file[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if ((*px).file[1] == -1)
			perror(0);
	}
	else
	{
		(*px).file[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0777);
		if ((*px).file[1] == -1)
			perror(0);
	}
}

void	init_fd(t_px *px)
{
	int	i;
	int	ps_num;

	ps_num = px->ps_num;
	(*px).fd = (int **)malloc(sizeof(int *) * (ps_num));
	if (!(*px).fd)
		throw_error(0);
	i = 0;
	while (i < ps_num)
	{
		(*px).fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(*px).fd[i++])
			throw_error(0);
	}
}
