/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:09:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 15:10:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	escape_minishell(void)
{
	write(1, "exit\n", 5);
	exit(g_errno);
}

char	*get_input(void)
{
	char *buf;
	char *tmp;

	buf = NULL;
	tmp = NULL;
	while (get_next_line(STDIN_FILENO, &tmp) == 0)
	{
		buf = ft_strjoin(buf, tmp);
		if (tmp[0])
		{
			g_eof = 1;
		}
		free(tmp);
		if (g_eof == 0)
		{
			ft_putchar_fd('\n', 1);
			free(buf);
			return (NULL);
		}
	}
	if (!buf)
		buf = tmp;
	return (buf);
}

void	minishell_loop(t_user *start, t_env *env)
{
	char	*user_input;

	change_pwd(env);
	catch_signal();
	while (1)
	{
		g_reg = 0;
		ft_printf("Minishell> ");
		if (!(user_input = get_input()))
			escape_minishell();
		g_eof = 0;
		if (ft_strcmp(user_input, "") != 0)
		{
			if (parsing_input(user_input, start, env) != -1)
			{
				if (conditionning(start) != -1)
				{
					execution(start, env);
				}
			}
			free_all(start);
		}
		free(user_input);
	}
}

int		main(int argc, char **argv, char **environnement)
{
	t_user	*start;
	t_env	*env;

	if (argc >= 2)
	{
		ft_printf("bash: %s: Aucun fochier ou dossier de ce type\n", argv[1]);
		exit(127);
	}
	if (!(start = malloc(sizeof(t_user))))
		malloc_error();
	if (!(env = malloc(sizeof(t_env))))
		malloc_error();
	env->tab = copy_double_tab(environnement);
	minishell_loop(start, env);
	return (0);
}
