/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:38:44 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/18 19:41:48 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_px {
	int		*pid;
	char	***cmd_args;
	int		**fd;
	int		file[2];
	int		ps_num;
}	t_px;

/* HELPERS */
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char	*src);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char	*s1,	char	*s2);
/* utilities */
char	**resolve_cmd(char *command, char **env);
char	*get_next_line(int fd, int buffer_size);
void	init_file(t_px *px, char **av, int ac);
void	init_fd(t_px *px);
void	ft_close(int **fd, int size, int *file);
// void	init_cmd(t_px *px, int ps_num, char **av, char **env);
void	throw_error(char *s);

#endif