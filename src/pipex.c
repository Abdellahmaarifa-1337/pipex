/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:53:42 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/14 19:25:15 by amaarifa         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	**cmd_arg_one;
	char	**cmd_arg_two;
	int		fd[2];
	int		fd_file;
	int		fd_file_2;
	int		pid1;
	int		pid2;

	(void)ac;
	fd_file = open(av[1], O_RDONLY);
	fd_file_2 = open(av[4], O_RDWR);
	cmd_arg_one = resolve_commands(av[2], env);
	cmd_arg_two = resolve_commands(av[3], env);
	if (pipe(fd) == -1)
		return (0);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd_file, 0);
		dup2(fd[1], 1);
		close(fd_file);
		close(fd_file_2);
		close(fd[0]);
		close(fd[1]);
		execve(cmd_arg_one[0], cmd_arg_one, env);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd_file_2, 1);
		dup2(fd[0], 0);
		close(fd_file);
		close(fd_file_2);
		close(fd[0]);
		close(fd[1]);
		execve(cmd_arg_two[0], cmd_arg_two, env);
	}
	close(fd_file);
	close(fd_file_2);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
