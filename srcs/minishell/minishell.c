/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:09:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 13:44:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function pour faire fonctionner le testeur de cacharles
** on peu la delete avant de passer en correction si on veut
*/

void	minishell_loop_test(t_user *start, t_env *env, char *argv)
{
	int		used;
	char	*user_input;

	(void)used;
	catch_signal();
	if (argv != NULL)
	{
		used = 0;
		g_reg = 0;
		user_input = ft_strdup(argv);
		if (ft_strcmp(user_input, "") != 0)
		{
			used = 1;
			if (parsing_input(user_input, start, env) != -1)
			{
				if (conditionning(start) != -1)
				{
					execution(start, env);
				}
				free_all(start);
			}
		}
		free(user_input);
	}
}

void	minishell_loop(t_user *start, t_env *env)
{
	int		used;
	int		ret;
	char	*user_input;

	(void)used;
	catch_signal();
	while (1)
	{
		used = 0;
		g_reg = 0;
		ft_printf("Minishell> ");
		ret = get_next_line(0, &user_input);
		verif_ret(ret, user_input);
		if (ft_strcmp(user_input, "") != 0)
		{
			used = 1;
			if (parsing_input(user_input, start, env) != -1)
			{
				free(user_input);
				if (conditionning(start) != -1)
				{
					execution(start, env);
				}
				free_all(start);
			}
		}
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
