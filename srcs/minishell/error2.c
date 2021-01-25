/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:54:00 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 13:56:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		malloc_error(void)
{
	strerror(errno);
	exit(EXIT_FAILURE);
}

void		print_trio_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
}

/*
** Error output from CD builtin
*/

void		var_name_error(int err, char *str)
{
	g_errno = err;
	print_trio_error("bash: export: « ", str \
					, " » : identifiant non valable\n");
}

int			dirr_error(char *path)
{
	g_errno = 1;
	print_trio_error("bash: cd: ", path, ": ");
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (0);
}

void		unset_error(char *str)
{
	print_trio_error("bash: unset: « ", str \
					, "» : identifiant non valable\n");
}
