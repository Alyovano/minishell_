/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 14:53:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_eof = 0;
		wait(NULL);
		ft_putchar_fd('\n', 1);
		if (g_reg != 1)
			ft_printf("Minishell> ");
		g_reg = -1;
	}
	else if (sig == SIGQUIT)
	{
		if (g_child_running)
			ft_printf("Quitter (core dumped)\n", sig);
	}
}

void		catch_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

/*
** Sert dans le cas du ctrl-D
*/

int			verif_ret(int ret, char *user_input)
{
	(void)user_input;
	if (ret == 0)
	{
		printf("%s\n", user_input);
		kill(-1, 0);
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
