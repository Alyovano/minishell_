/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 09:28:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Export recoit la structure avec le tableau d'environnement
** et l'argument qui suit l'appel de export
** Si pas d'argu : il print le tableau
** Si argu, il le parse, et ajoute le(s) vars si elles sont valides
** dans un cas invalide il retourne une erreur
*/

/*
** Prend l'argument, la nombre de de coupe (size) et
** le tableau fournit par la fonction precedente, renvoie
** le tableau remplit par chaque morceau de l'argument
*/

/*
** j start a 1 parce que la case 0 de lst->tab_cmd[] c'est le nom de
** la buitin - export dans ce cas-ci, et ca ne fait pas partie de l'argu
*/

int			is_valid_name(char *str)
{
	int i;
	int alphabet_token;

	i = 0;
	alphabet_token = 0;
	while (str[i])
	{
		if (is_valid_char(str[i]) == 0)
		{
			if (i == 0 && ft_isdigit(str[i]) == 1)
				return (-1);
			if (ft_isalpha(str[i]) == 1)
				alphabet_token = 1;
		}
		else
			return (-1);
		i++;
	}
	if (alphabet_token == 0)
		return (-1);
	return (0);
}

void		init_export_new_var(t_export_new_var *a, t_list *lst, t_env *env)
{
	a->new_tab = malloc(sizeof(a->new_tab) *
		(double_tab_size(env->tab) + double_tab_size(lst->tab_cmd)) + 2);
	if (a->new_tab == NULL)
		malloc_error();
	a->i = 0;
	a->j = 1;
}

void		export_new_var_copy(t_export_new_var *a, t_list *lst)
{
	if (is_valid_name(lst->tab_cmd[a->j]) == 0)
	{
		a->position = check_if_exist(a->new_tab, lst->tab_cmd[a->j]);
		if (a->position != -1)
		{
			a->tmp = change_value(a->new_tab[a->position], lst->tab_cmd[a->j]);
			free(a->new_tab[a->position]);
			a->new_tab[a->position] = ft_strdup(a->tmp);
			free(a->tmp);
			a->j++;
		}
		else
		{
			a->new_tab[a->i] = ft_strdup(lst->tab_cmd[a->j]);
			a->j++;
			a->i++;
			a->new_tab[a->i] = NULL;
		}
	}
	else
	{
		g_errno = 1;
		ft_printf("minishell: export: « %s » : identifiant non valable\n",
			lst->tab_cmd[a->j]);
		a->j++;
	}
}

int			export_new_var(t_env *env, t_list *lst)
{
	t_export_new_var a;

	init_export_new_var(&a, lst, env);
	while (env->tab[a.i])
	{
		a.new_tab[a.i] = ft_strdup(env->tab[a.i]);
		a.i++;
	}
	a.new_tab[a.i] = NULL;
	while (lst->tab_cmd[a.j])
		export_new_var_copy(&a, lst);
	a.new_tab[a.i] = NULL;
	//free_double_tab(env->tab);
	env->tab = copy_double_tab(a.new_tab);
	free_double_tab(a.new_tab);
	a.i = 0;
	while (env->tab[a.i])
	{
		//free(env->tab[a.i]);
		env->tab[a.i] = delete_quote(env->tab[a.i]);
		a.i++;
	}
	return (0);
}

int			ft_export(t_env *env, t_list *lst)
{
	int quote_add;

	env->swap_token = 0;
	quote_add = 0;
	if (double_tab_size(lst->tab_cmd) == 1)
	{
		env->export = copy_double_tab(env->tab);
		while (env->export[quote_add])
		{
			env->export[quote_add] = delete_quote(env->export[quote_add]);
			env->export[quote_add] = requote_str(env->export[quote_add]);
			quote_add++;
		}
		sort_export(env);
		export_without_args(env);
		free_double_tab(env->export);
		return (NO_ARGS);
	}
	else
	{
		requote_arg(lst);
		export_new_var(env, lst);
		return (ARGS);
	}
	return (-1);
}
