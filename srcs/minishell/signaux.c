/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 10:53:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		wait(NULL);
		ft_putchar_fd('\n', 1);
		if (g_reg != 1)
			ft_printf("Minishell> ");
		g_reg = -1;
	}
}

void		catch_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
** Sert dans le cas du ctrl-D
*/

int			verif_ret(int ret, char *user_input)
{
	(void)user_input;
	if (ret == 0)
	{
		kill(-1, 0);
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
		//ICI MEGA FREE SORTIE CTRL-D
		// NE PAS DELETE CE COM TANT QUE C EST PAS FAIT
	}
	return (0);
}
