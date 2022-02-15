/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:30:22 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/15 18:06:39 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_px(t_px px, char **av, int ac, int ps_num, char **env)
{
	int	i;

	if (strcmp(av[1], "here_doc"))
		px.file[0] = open(av[1], O_RDONLY);
	px.file[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	px.fd = (int **)malloc(sizeof(int *) * (ps_num - 1));
	i = 0;
	while (i < ps_num - 1)
		px.fd[i++] = (int *)malloc(sizeof(int) * 2);
	px.cmd_args = (char ***)malloc(sizeof(int **) * ps_num);
	i = 0;
	while (i < ps_num)
	{
		if (strcmp(av[1], "here_doc"))
			px.cmd_args[i] = resolve_cmd(av[i + 3], env);
		else
			px.cmd_args[i] = resolve_cmd(av[i + 2], env);
		i++;
	}
	px.pid = (int *)malloc(sizeof(int) * ps_num);
}

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
	close(file[0]);
	close(file[1]);
}
void	ft_dup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}
int	main (int ac, char **av, char **env)
{
	t_px	px;
	int		i;
	int		ps_num;

	if (ac < 4)
		return (0);
	if (!strcmp(av[1], "here_doc"))
		ps_num = ac - 4;
	else
		ps_num = ac - 3;
	init_px(px, av, ac, ps_num, env);
	i = 0;
	while (i < ps_num - 1)
		pipe(px.fd[i++]);
	px.pid[0] = fork();
	i = 0;
	while (i < ps_num)
	{
		if (i != 0 && px.pid[i - 1] != 0)
			px.pid[i] = fork();
		if (px.pid[i] == 0)
		{
			if (i == 0)
				ft_dup(px.file[0], px.fd[i][1]);
			else if (i == ps_num - 1)
				ft_dup(px.fd[i - 1][0], px.file[1]);
			else
				ft_dup(px.fd[i - 1][0], px.fd[i][1]);
			ft_close(px.fd, ps_num - 1, px.file);
			execve(px.cmd_args[i][0], px.cmd_args[i], env);
		}
		i++;
	}
	ft_close(px.fd, ps_num - 1, px.file);
	wait(NULL);
	return (0);
}