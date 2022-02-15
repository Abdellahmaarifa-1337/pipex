/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:53:42 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/15 17:07:43 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
 'ls -l -a -h' 
*/



void	ft_close(int n, int **fd, int size, int *file)
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

/*
	1- TAKE THE IN FILE AND THE OUT FILE FROM ARGS
	2- MAKE A PROCCES FOR EACH COMMAND
*/


int	main(int ac, char **av, char **env)
{
	// char	**cmd_arg_one;
	// char	**cmd_arg_two;
	// int		fd[2];
	// int		file[2];
	// int		pid[2];

	// cmd_arg_one = resolve_commands(av[2], env);
	// cmd_arg_two = resolve_commands(av[3], env);
	// file[0] = open(av[1], O_RDONLY);
	// file[1] = open(av[ac - 1], O_RDWR | O_CREAT);
	// pipe(fd);
	// pid[0] = fork();
	// if (pid[0] == 0)
	// {
	// 	ft_dup(file[0], fd[1]);
	// 	ft_close(fd, file);
	// 	execve(cmd_arg_one[0], cmd_arg_one, env);
	// }
	// pid[1] = fork();
	// if (pid[1] == 0)
	// {
	// 	ft_dup(fd[0], file[1]);
	// 	ft_close(fd, file);
	// 	execve(cmd_arg_two[0], cmd_arg_two, env);
	// }
	// ft_close(fd, file);
	// waitpid(pid[0], NULL, 0);
	// waitpid(pid[1], NULL, 0);

	int 	num_p = ac - 3; // number of CMD
	int 	pid[ac - 3];
	char	**cmd_args[ac - 3];
	int 	**fd;
	int 	i = 0;
	int		file[2];

	fd = (int **)malloc(sizeof(int *) * (ac - 4));

	i = 0;
	while (i < ac - 4)
	{	
		fd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	file[0] = open(av[1], O_RDONLY);
	file[1] = open(av[ac - 1], O_RDWR | O_CREAT, 0777);
	// resloving the cmd args
	while (i < ac - 3)
	{
		cmd_args[i] = resolve_commands(av[i + 2], env);
		i++;
	}

	i = 0;
	while (i < ac - 4)
	{
		pipe(fd[i]);
		i++;
	}

	i = 0;
	pid[0] = fork();
	while (i < num_p)
	{
		if (i != 0 && pid[i - 1] != 0)
			pid[i] = fork();
		if (pid[i] == 0)
		{
			printf("%d and %d\n", i, num_p);
			if (i == 0)
			{
				ft_dup(file[0], fd[i][1]);
			}
			else if (i == num_p - 1)
			{
				ft_dup(fd[i - 1][0], file[1]);
			}
			else			
				ft_dup(fd[i - 1][0], fd[i][1]);
			ft_close(ac - 4,fd, ac - 4, file);
			execve(cmd_args[i][0], cmd_args[i], env);
			printf("cmd running..\n");
			exit(0);
		}
		//pid[++i] = fork();
		i++;
	}
	ft_close(ac - 4, fd, ac - 4, file);
	wait(NULL);
	return (0);
}
