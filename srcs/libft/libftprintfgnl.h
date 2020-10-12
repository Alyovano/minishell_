/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintfgnl.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:22:23 by alyovano          #+#    #+#             */
/*   Updated: 2020/10/12 08:50:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTFGNL_H
# define LIBFTPRINTFGNL_H
# include "./srcs/ft_printf/ft_printf.h"
# include "./srcs/libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>

int				get_next_line(int fd, char **line);

#endif
