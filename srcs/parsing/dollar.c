/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 10:45:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/18 14:42:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_var_in_env(char *var_name, t_env *env)
{
	int		i;
	int		token_copy;
	char	*new;

	i = 0;
	token_copy = 0;
	while (env->tab[i])
	{
		if (str_check(env->tab[i], var_name) == 0)
		{
			if (env->tab[i])
				token_copy = 1;
			break ;
		}
		i++;
	}
	if (token_copy == 1)
		new = ft_substr(env->tab[i], ft_strlen(var_name) + 1, \
											ft_strlen(env->tab[i]));
	else
		new = ft_strdup("");
	return (new);
}

/*
**ici start->user_cmd_tab[i][j] == '$' au depart
**k represente la len du nom de la variable d'envi
**Je suis pas sur dans la while pour : start->user_cmd_tab[i][j] != '='
*/

// ne pas oublier de placer les free ici

int		dollar_var_name(t_user *start, int i, int j, t_dollar *dol, t_env *env)
{
	int		tmp;
	int		k;
	char	*one;
	char	*two;

	j += 1;
	tmp = j;
	k = 0;
	while (start->user_cmd_tab[i][j + k] && start->user_cmd_tab[i][j + k] != ' '
	&& start->user_cmd_tab[i][j + k] != '\'' && start->user_cmd_tab[i][j + k] != '"'
	&& start->user_cmd_tab[i][j + k] != '=' && start->user_cmd_tab[i][j + k] != '.')
		k++;
	dol->var_name = ft_substr(start->user_cmd_tab[i], tmp, k);
	dol->var_content = check_var_in_env(dol->var_name, env);
	dol->before_str = ft_substr(start->user_cmd_tab[i], 0, j - 1);
	dol->after_str = ft_substr(start->user_cmd_tab[i], j + k, ft_strlen(start->user_cmd_tab[i]));
	one = ft_strjoin(dol->before_str, dol->var_content);
	two = ft_strjoin(one, dol->after_str);
	free(start->user_cmd_tab[i]);
	start->user_cmd_tab[i] = ft_strdup(two);
	tmp = ft_strlen(one);
	//free_dol(dol, one, two);
	// if (dol->var_name != NULL)
	// 	free(dol->var_name);
	return (tmp);
}

/*
** remplace $? par la valeur de retour precedente
** Retourne la taille de la valeur de $?
*/

int		previous_return_value(t_user *start, int i, int j, t_dollar *dol)
{
	int		int_size;
	char	*value;
	char	*one;
	char	*two;

	int_size = 0;
	value = ft_itoa(g_errno);
	j += 1;
	dol->before_str = ft_substr(start->user_cmd_tab[i], 0, j - 1);
	dol->after_str = ft_substr(start->user_cmd_tab[i], j + 1, \
									ft_strlen(start->user_cmd_tab[i]));
	one = ft_strjoin(dol->before_str, value);
	two = ft_strjoin(one, dol->after_str);
	free(start->user_cmd_tab[i]);
	start->user_cmd_tab[i] = ft_strdup(two);
	int_size = ft_strlen(one);
	return (int_size);
}

/*
** j = check_simple_quote(start, quote, j, i);// jump sur la char apres la squote
*/

int		check_dollar_or_not_dollar(t_user *start,
						t_quote *quote, int i, t_dollar *dol, t_env *env)
{
	int j;
	int token;

	j = 0;
	quote->dollar_quote = 0;
	while (start->user_cmd_tab[i][j])
	{
		token = 0;
		j = check_simple_quote(start, quote, j, i);
		if (start->user_cmd_tab[i][j] == '$' &&
					(get_backslash(start->user_cmd_tab[i], j) == 0)
					&& (start->user_cmd_tab[i][j + 1])
					&& (start->user_cmd_tab[i][j + 1] != ' ')
					&& (start->user_cmd_tab[i][j + 1] != '"'))
		{
			if (start->user_cmd_tab[i][j + 1] && (start->user_cmd_tab[i][j + 1] == '?'))
			{
				token = 1;
				j = previous_return_value(start, i, j, dol);
			}
			else
				j = dollar_var_name(start, i, j, dol, env);
		}
		if (token != 1)
			j++;
	}
	return (0);
}

int		add_environnement_var(t_user *start, t_quote *quote, t_env *env)
{
	int			i;
	t_dollar	*dol;

	dol = malloc(sizeof(dol));
	if (!dol)
		malloc_error();
	i = 0;
	dol->start_cut = 0;
	while (start->user_cmd_tab[i])
	{
		check_dollar_or_not_dollar(start, quote, i, dol, env);
		i++;
	}
	free(dol);
	return (0);
}
