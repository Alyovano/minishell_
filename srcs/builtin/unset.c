/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 15:12:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			**copy_unset_tab(char **src)
{
	char	**new_tab;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = double_tab_size(src);
	new_tab = malloc(sizeof(char *) * (size + 1));
	if (!new_tab)
		malloc_error();
	new_tab[size] = 0;
	while (src[i])
	{
		if (ft_strcmp("123456789", src[i]) != 0)
		{
			new_tab[j] = ft_strdup(src[i]);
			j++;
		}
		i++;
	}
	new_tab[j] = NULL;
	return (new_tab);
}

char			**check_var_name(char **arg)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * (double_tab_size(arg) + 1));
	if (!tmp)
		malloc_error();
	while (arg[i])
	{
		if (is_valid_name(arg[i]) == -1)
			unset_error(arg[i++]);
		else
		{
			tmp[j] = ft_strdup(arg[i]);
			i++;
			j++;
		}
	}
	tmp[j] = NULL;
	free_double_tab(arg);
	return (tmp);
}

/*
** Unset creer un nouveau tableau sans les variables detruire par user
** Le code "123456789" indique a la fonction quelle var
** va etre delete dans la creation du suivant
** ce nom ne porte pas a confusion puisqu'il ne peut pas etre utilise
** par user -> check_var_name(tmp); bloque son accessibilite
*/

void			init_unset(t_export_new_var *a, t_list *lst)
{
	a->i = 0;
	a->j = 0;
	while (lst->tab_cmd[a->i])
	{
		lst->tab_cmd[a->i] = delete_quote(lst->tab_cmd[a->i]);
		a->i++;
	}
	a->i = 0;
}

void			delete_env_var(t_list *lst, t_export_new_var *a, t_env *env)
{
	a->j = 0;
	while (env->tab[a->j])
	{
		if (catch_env_varr(lst->tab_cmd[a->i], env->tab[a->j]) == 0)
		{
			free(env->tab[a->j]);
			env->tab[a->j] = ft_strdup("123456789");
		}
		a->j++;
	}
	a->i++;
}

int				ft_unset(t_env *env, t_list *lst)
{
	t_export_new_var a;

	init_unset(&a, lst);
	while (lst->tab_cmd[a.i])
	{
		if (is_valid_name(lst->tab_cmd[a.i]) == 0)
		{
			delete_env_var(lst, &a, env);
		}
		else
		{
			unset_error(lst->tab_cmd[a.i]);
			a.i++;
		}
	}
	a.new_tab = copy_unset_tab(env->tab);
	free_double_tab(env->tab);
	env->tab = copy_double_tab(a.new_tab);
	free_double_tab(a.new_tab);
	return (0);
}
