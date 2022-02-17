/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:30:22 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/17 22:09:45 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	ft_close(int **fd, int size, int *file)
{
	int 	i;

	i = 0;
	while (i < size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	if (file[0] && file[0] != 1)
		close(file[0]);
	if (file[1] && file[1] != 1)
		close(file[1]);
}

void	ft_dup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	set_in_out(t_px *px, char **av, int here_doc)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	if (here_doc)
	{
		line = get_next_line(0, 100);
		while (line && strcmp(line, ft_strjoin(av[2], "\n")))
		{
			temp = get_next_line(0, 100);
			if(!temp || !strcmp(temp, ft_strjoin(av[2], "\n")))
				break ;
			line = ft_strjoin(line, temp);
			free(temp);
		}
		write((*px).fd[i][1], line, strlen(line));
	}
	else 
		(*px).fd[i][0] = (*px).file[0];
}

void	pip_cmd(t_px *px, int ps_num, char **env, char **av)
{
	int		i;
	int		here_doc;
	char	**resloved_cmd;
	here_doc = !strcmp(av[1], "here_doc");
	i = 0;
	while (i < ps_num)
	{
		(*px).pid[i] = fork();						
		if ((*px).pid[i] == 0)
		{
			if (i == ps_num - 1)
				ft_dup((*px).fd[i][0], (*px).file[1]);
			else
				ft_dup((*px).fd[i][0], (*px).fd[i + 1][1]);
			ft_close((*px).fd, ps_num, (*px).file);
			if (here_doc)
				resloved_cmd = resolve_cmd(av[i + 3], env);
			else
				resloved_cmd = resolve_cmd(av[i + 2], env);
			execve(resloved_cmd[0], resloved_cmd, env);
			ft_close((*px).fd, ps_num, (*px).file);

			perror(0);
			exit(0);
		}
		i++;
	}
	ft_close((*px).fd, ps_num, (*px).file);
	i = 0;
	while(i++ < ps_num)
		wait(NULL);
}

int	main (int ac, char **av, char **env)
{
	t_px	px;
	int		i;
	int		ps_num;
	int		here_doc;

	here_doc = !strcmp(av[1], "here_doc");
	if (!here_doc && ac < 5)
		throw_error("Erorr : You have to provide at least 4 args\n");
	else if(here_doc && ac < 6)
		throw_error("Erorr : You have to provide at least 5 args\n");
	if (here_doc)
		ps_num = ac - 4;
	else
		ps_num = ac - 3;
	init_file(&px, av, ac);
	init_fd(&px, ps_num);
	//init_cmd(&px, ps_num, av, env);
	px.pid = (int *)malloc(sizeof(int) * ps_num);
	if (!px.pid)
		throw_error(0);
	i = -1;
	while (++i < ps_num)
		pipe(px.fd[i]);
	set_in_out(&px, av, here_doc);
	pip_cmd(&px, ps_num, env, av);
	return (0);
}