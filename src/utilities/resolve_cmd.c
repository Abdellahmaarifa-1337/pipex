/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:07:45 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/15 17:08:23 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

char	**resolve_cmd(char *command, char **env)
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