/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 10:45:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 13:03:01 by user42           ###   ########.fr       */
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

int		dollar_var_name(t_list *lst, int i, int j, t_dollar *dol, t_env *env)
{
	int		tmp;
	int		k;
	char	*one;
	char	*two;

	j += 1;
	tmp = j;
	k = 0;
	while (lst->tab_cmd[i][j + k] && lst->tab_cmd[i][j + k] != ' '
	&& lst->tab_cmd[i][j + k] != '\'' && lst->tab_cmd[i][j + k] != '"'
	&& lst->tab_cmd[i][j + k] != '=' && lst->tab_cmd[i][j + k] != '.'
	&& lst->tab_cmd[i][j + k] != '$')
		k++;
	dol->var_name = ft_substr(lst->tab_cmd[i], tmp, k);
	dol->var_content = check_var_in_env(dol->var_name, env);
	dol->before_str = ft_substr(lst->tab_cmd[i], 0, j - 1);
	dol->after_str = ft_substr(lst->tab_cmd[i], j + k, ft_strlen(lst->tab_cmd[i]));
	one = ft_strjoin(dol->before_str, dol->var_content);
	two = ft_strjoin(one, dol->after_str);
	if (lst->tab_cmd[i])
		free(lst->tab_cmd[i]);
	lst->tab_cmd[i] = ft_strdup(two);
	tmp = ft_strlen(one) - 1;
	free_dol(dol, one, two);
	return (tmp);
}

/*
** remplace $? par la valeur de retour precedente
** Retourne la taille de la valeur de $?
*/

int		previous_return_value(t_list *lst, int i, int j, t_dollar *dol)
{
	int		int_size;
	char	*value;
	char	*one;
	char	*two;

	int_size = 0;
	value = ft_itoa(g_errno);
	j += 1;
	dol->before_str = ft_substr(lst->tab_cmd[i], 0, j - 1);
	dol->after_str = ft_substr(lst->tab_cmd[i], j + 1, \
									ft_strlen(lst->tab_cmd[i]));
	one = ft_strjoin(dol->before_str, value);
	two = ft_strjoin(one, dol->after_str);
	free(lst->tab_cmd[i]);
	lst->tab_cmd[i] = ft_strdup(two);
	int_size = ft_strlen(one);
	free_dol2(dol, one, two);
	free(value);
	return (int_size);
}

/*
** j = check_simple_quote(start, quote, j, i);// jump sur la char apres la squote
*/

int		check_dollar_or_not_dollar(t_list *lst, int i, t_quote *quote, t_dollar *dol, t_env *env)
{
	int j;
	int token;

	j = 0;
	quote->dollar_quote = 0;
	while (lst->tab_cmd[i][j])
	{
		token = 0;
		if (lst->tab_cmd[i][j] == '$' &&
			(get_backslash(lst->tab_cmd[i], j) == 0)
			&& (lst->tab_cmd[i][j + 1])
			&& (lst->tab_cmd[i][j + 1] != ' ')
			&& (!(j != 0 && lst->tab_cmd[i][j - 1] == '\''))) //&& (lst->tab_cmd[i][j + 1] != '"'))
			
		{
			if (lst->tab_cmd[i][j + 1] == '?')
			{
				token = 1;
				j = previous_return_value(lst, i, j, dol);
			}
			else
			{
				j = dollar_var_name(lst, i, j, dol, env);
			}
			
		}
		if (token != 1)
			j++;
	}
	return (0);
}

int		add_environnement_var(t_list *lst, t_env *env)
{
	int			i;
	t_dollar	*dol;
	t_list		*tmp;
	t_quote		quote;

	dol = malloc(sizeof(t_dollar));
	if (!dol)
		malloc_error();
	i = 0;
	dol->start_cut = 0;
	tmp = lst;
	while (lst)
	{
		i = 0;
		while (lst->tab_cmd[i])
		{
			check_dollar_or_not_dollar(lst, i, &quote, dol, env);
			i++;
		}
		lst = lst->next;
	}
	lst = tmp;
	free(dol);
	return (0);
}
