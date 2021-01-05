/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyovano <alyovano@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:28:10 by alyovano          #+#    #+#             */
/*   Updated: 2020/01/17 14:07:46 by alyovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr(char *str)
{
	if (str)
	{
		write(1, str, ft_strlen(str));
	}
}

void		ft_putstr_color(char const *s, char *str)
{
	ft_putstr(str);
	if (s)
	{
		while (*s)
			ft_putchar_fd(*s++, 1);
	}
	ft_putstr("\e[0m");
}

int			ft_putstr_fd(char *s, int fd)
{
	unsigned int	size;

	size = ft_strlen(s);
	if (s)
		write(fd, s, size);
	return (size);
}
