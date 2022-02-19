/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:33:01 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/19 16:39:05 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
	free_arr(resloved_cmd);
	exit(0);
}

void	pip_cmd(t_px *px, char **env, char **av)
{
	int		i;

	i = 0;
	while (i < px->ps_num)
	{
		(*px).pid[i] = fork();
		if ((*px).pid[i] == -1)
			throw_error(0);
		if ((*px).pid[i] == 0)
			exec_cmd(px, i, av, env);
		i++;
	}
	ft_close((*px).fd, px->ps_num, (*px).file);
	i = 0;
	while (i++ < px->ps_num)
		wait(NULL);
}
