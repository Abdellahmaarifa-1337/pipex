/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:38:44 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/15 18:03:11 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
typedef struct s_px {
	int		*pid;
	char	***cmd_args;
	int		**fd;
	int		file[2];
}	t_px;

/* HELPERS */
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char	*src);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

/* utilities */
char	**resolve_cmd(char *command, char **env);

#endif