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
**/

/*
** Prend l'argument, la nombre de de coupe (size) et
** le tableau fournit par la fonction precedente, renvoie
** le tableau remplit par chaque morceau de l'argument
*/

/*
** j start a 1 parce que la case 0 de lst->tab_cmd[] c'est le nom de 
** la buitin - export dans ce cas-ci, et ca ne fait pas partie de l'argu
*/

int			is_valid_char(char c)
{
	if (c == '[' || c == ']' || c == '!'
		|| c == '@' || c == '#' || c == '$' || c == '%'
		|| c == '^' || c == '&' || c == '*' || c == '{'
		|| c == '}' || c == '.' || c == ',' || c == '?'
		|| c == ':')
		return (-1);
	return (0);
}

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

int			export_new_var(t_env *env, t_list *lst)
{
	char **new_tab;
	char *tmp;
	int i;
	int j;
	int position;

	new_tab = malloc(sizeof(new_tab) * (double_tab_size(env->tab) + double_tab_size(lst->tab_cmd)) + 2);
	if (!new_tab)
		malloc_error();
	i = 0;
	j = 1;
	while (env->tab[i])
	{
		new_tab[i] = ft_strdup(env->tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	while (lst->tab_cmd[j])
	{
		if (is_valid_name(lst->tab_cmd[j]) == 0)
		{
			position = check_if_exist(new_tab, lst->tab_cmd[j]);
			if (position != -1)
			{
				tmp = replace_var_value(new_tab[position], lst->tab_cmd[j]);
				free(new_tab[position]);
				new_tab[position] = ft_strdup(tmp);
				free(tmp);
				j++;
			}
			else
			{
				new_tab[i] = ft_strdup(lst->tab_cmd[j]);
				j++;
				i++;
				new_tab[i] = NULL;
			}
		}
		else
		{
			ft_printf("minishell: export: « %s » : identifiant non valable\n", lst->tab_cmd[j]);
			j++;
		}
	}
	new_tab[i] = NULL;

	// Free le vieux tableau d'env
	//free_double_tab(env->tab);
	// ici ce free est grave chelou
	//printf("4\n");
	// i = 0;
	// while (env->tab[i])
	// {
	// 	printf("%d\n", i);
	// 	printf("La str a free :%s\n", env->tab[i]);
	// 	if (i != 1)
	// 		free(env->tab[i]);
	// 	printf("FREE OK\n");
	// 	i++;
	// }
	// free(env->tab);

	// Copie du nouveau tableau dans ENV
	env->tab = copy_double_tab(new_tab);
	free_double_tab(new_tab);
	return (0);
}

char		*requote_str(char *str)
{
	int		i;
	int		j;
	char	*new;
	int		token;

	new = malloc((sizeof(char*) * ft_strlen(str)) + 3);
	if (!new)
		malloc_error();
	i = 0;
	j = 0;
	token = 0;
	while (str[i])
	{
		new[i + j] = str[i];
		if (token == 0 && str[i] == '=')
		{
			token = 1;
			j = 1;
			new[i + j] = '"';
		}
		i++;
	}
	if (token == 1)
	{
		new[i + j] = '"';
		new[i + j + 1] = 0;
	}
	else
		new[i] = 0;
	free(str);
	return (new); 
}

void		requote_arg(t_list *lst)
{
	int i;

	i = 0;
	while (lst->tab_cmd[i])
	{
		lst->tab_cmd[i] = delete_quote(lst->tab_cmd[i]);
		lst->tab_cmd[i] = requote_str(lst->tab_cmd[i]);
		i++;
	}
}

/*
** CERTAINES VAR DOIVENT ETRE REFUSEES CAR
** ELLES COMPORTENT DES []$%#@!
** TO DO
*/

int         ft_export(t_env *env, t_list *lst)
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
	// status = 1 ici
    return (-1);
}
