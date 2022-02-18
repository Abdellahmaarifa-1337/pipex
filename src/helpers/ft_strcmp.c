/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:45:43 by amaarifa          #+#    #+#             */
/*   Updated: 2022/02/18 18:46:02 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char	*s1,	char	*s2)
{
	unsigned char	*a;
	unsigned char	*b;
	int				i;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	while (a[i] == b[i] && a[i] && b[i])
		i++;
	return (a[i] - b[i]);
}
