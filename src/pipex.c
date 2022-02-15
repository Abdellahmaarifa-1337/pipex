/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:53:42 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/15 10:20:10 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
 'ls -l -a -h' 
*/

char	**resolve_path(char **env)
{
	int		i;
	char	*s;

	i = 0;
	while (env[i])
	{
		if (ft_strlen(env[i]) > 4)
		{
			if (env[i][0] == 'P' && env[i][1] == 'A'
				&& env[i][2] == 'T' && env[i][3] == 'H')
			{
				s = env[i] + 5;
				return (ft_split(s, ':'));
			}
		}
		i++;
	}
	return (0);
}

char	*get_right_path(char *command, char **path)
{
	int		i;
	char	*cmd;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(temp, command);
		free(temp);
		if (access(cmd, 777) == 0)
			return (cmd);
		i++;
	}
	return (0);
}

char	**resolve_commands(char *command, char **env)
{
	char	**command_arg;
	char	*full_path;
	char	**path;

	command_arg = ft_split(command, ' ');
	path = resolve_path(env);
	full_path = get_right_path(command_arg[0], path);
	if (!full_path)
	{
		printf("Error\n");
		exit(1);
	}
	command_arg[0] = full_path;
	return (command_arg);
}

void	ft_close(int *fd, int fd_size, int *file)
{
	int	i;

	i = 0;
	while (i < fd_size)
		close(fd[i++]);
	close(file[0]);
	close(file[1]);
}

ft_dup(int in, int out)
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
	char	**cmd_arg_one;
	char	**cmd_arg_two;
	int		fd[2];
	int		file[2];
	int		pid[1];
	
	cmd_arg_one = resolve_commands(av[2], env);
	cmd_arg_two = resolve_commands(av[3], env);
	if (pipe(fd) == -1)
		return (0);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		file[0] = open(av[1], O_RDONLY);
		ft_dup(file[0], fd[1]);
		ft_close(fd, 2, file);
		execve(cmd_arg_one[0], cmd_arg_one, env);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		file[1] = open(av[4], O_RDWR | O_CREAT);
		ft_dup(fd[0], file[1]);
		ft_close(fd, 2, file);
		execve(cmd_arg_two[0], cmd_arg_two, env);
	}
	ft_close(fd, 2, file);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
