/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:30:22 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/19 15:51:50 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	set_in_out(t_px *px, char **av, int here_doc)
{
	char	*line;
	char	*temp;
	char	*delm;
	char	*prev;

	if (here_doc)
	{
		line = ft_strdup("");
		delm = ft_strjoin(av[2], "\n");
		while (1)
		{
			temp = get_next_line(0, 100);
			if (!ft_strcmp(temp, delm))
				break ;
			prev = line;
			line = ft_strjoin(prev, temp);
			free(prev);
			free(temp);
		}
		free(delm);
		write((*px).fd[0][1], line, strlen(line));
		free(line);
	}
	else
		(*px).fd[0][0] = (*px).file[0];
}

void	init_ps_num(t_px *px, char **av, int ac)
{
	int		here_doc;

	here_doc = !ft_strcmp(av[1], "here_doc");
	if (!here_doc && ac < 5)
		throw_error("Erorr : You have to provide at least 4 args\n");
	else if (here_doc && ac < 6)
		throw_error("Erorr : You have to provide at least 5 args\n");
	if (here_doc)
		px->ps_num = ac - 4;
	else
		px->ps_num = ac - 3;
}

int	main(int ac, char **av, char **env)
{
	t_px	px;
	int		i;
	int		ps_num;
	int		here_doc;

	here_doc = !ft_strcmp(av[1], "here_doc");
	init_ps_num(&px, av, ac);
	init_fd(&px);
	px.pid = (int *)malloc(sizeof(int) * ps_num);
	if (!px.pid)
		throw_error(0);
	i = -1;
	while (++i < px.ps_num)
		if (pipe(px.fd[i]) == -1)
			throw_error(0);
	init_file(&px, av, ac);
	set_in_out(&px, av, here_doc);
	pip_cmd(&px, env, av);
	return (0);
}
