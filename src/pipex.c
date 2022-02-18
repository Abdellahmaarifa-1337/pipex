/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:30:22 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/18 19:41:27 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	ft_dup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

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

void	exec_cmd(t_px *px, int i, char **av, char **env)
{
	char	**resloved_cmd;
	int		here_doc;

	here_doc = !ft_strcmp(av[1], "here_doc");
	if (i == 0 && (*px).file[0] == -1)
	{
		ft_close((*px).fd, px->ps_num, (*px).file);
		exit(0);
	}
	if (i == px->ps_num - 1)
		ft_dup((*px).fd[i][0], (*px).file[1]);
	else
		ft_dup((*px).fd[i][0], (*px).fd[i + 1][1]);
	ft_close((*px).fd, px->ps_num, (*px).file);
	if (here_doc)
		resloved_cmd = resolve_cmd(av[i + 3], env);
	else
		resloved_cmd = resolve_cmd(av[i + 2], env);
	execve(resloved_cmd[0], resloved_cmd, env);
	ft_close((*px).fd, px->ps_num, (*px).file);
	perror(0);
	exit(0);
}

void	pip_cmd(t_px *px, char **env, char **av)
{
	int		i;

	i = 0;
	while (i < px->ps_num)
	{
		(*px).pid[i] = fork();
		if ((*px).pid[i] == 0)
			exec_cmd(px, i, av, env);
		i++;
	}
	ft_close((*px).fd, px->ps_num, (*px).file);
	i = 0;
	while (i++ < px->ps_num)
		wait(NULL);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	t_px	px;
	int		i;
	int		ps_num;
	int		here_doc;

	here_doc = !ft_strcmp(av[1], "here_doc");
	if (!here_doc && ac < 5)
		throw_error("Erorr : You have to provide at least 4 args\n");
	else if (here_doc && ac < 6)
		throw_error("Erorr : You have to provide at least 5 args\n");
	if (here_doc)
		px.ps_num = ac - 4;
	else
		px.ps_num = ac - 3;
	init_fd(&px);
	px.pid = (int *)malloc(sizeof(int) * ps_num);
	if (!px.pid)
		throw_error(0);
	i = -1;
	while (++i < px.ps_num)
		pipe(px.fd[i]);
	init_file(&px, av, ac);
	set_in_out(&px, av, here_doc);
	pip_cmd(&px, env, av);
	return (0);
}
