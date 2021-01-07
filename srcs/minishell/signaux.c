/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 13:49:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		sig_handler(int sig)
{
	(void)sig;
	//char buf[PATH_CWD_MAX + 1];

	wait(NULL);
	ft_putchar_fd('\n', 1);
	if (g_reg != 1)
		ft_printf("Minishell> ");	//print_promt(getcwd(buf, sizeof(buf)));
	g_reg = -1;
}

void		catch_signal(void)
{
	signal(SIGINT, sig_handler);
}

/*
** Sert dans le cas du ctrl-D
*/

int			verif_ret(int ret, char *user_input)
{
	(void)user_input;
	if (ret == 0)
	{
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
		//ICI MEGA FREE SORTIE CTRL-D
		// NE PAS DELETE CE COM TANT QUE C EST PAS FAIT
	}
	return (0);
}
