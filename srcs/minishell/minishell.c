/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:09:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 16:38:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function pour faire fonctionner le testeur de cacharles
** on peu la delete avant de passer en correction si on veut
*/

void	minishell_loop_test(t_user *start, t_env *env, char *argv)
{
	char	*user_input;

	change_pwd(env);
	catch_signal();
	if (argv != NULL)
	{
		g_reg = 0;
		user_input = ft_strdup(argv);
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

char	*get_input()
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
			g_errno = 1;
			ft_putchar_fd('\n', 1);
			free(buf);
			return (NULL);
		}
	}
	if (!buf)
		buf = tmp;
	g_errno = 0;
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
			exit(EXIT_FAILURE);
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

	if (!(start = malloc(sizeof(t_user))))
		malloc_error();
	if (!(env = malloc(sizeof(t_env))))
		malloc_error();
	env->tab = copy_double_tab(environnement);
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0)
		minishell_loop_test(start, env, argv[2]);
	else
		minishell_loop(start, env);
	return (0);
}
