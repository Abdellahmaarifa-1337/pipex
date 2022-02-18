/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:34:40 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/18 19:39:49 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_close(int **fd, int size, int *file)
{
	int	i;

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
