/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:55:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** s1 = Mon argu a chercher dans le tableau
** s2 = la ligne du tableau 
**
** return 0 -> La var existe dans le tableau
** return 1 -> Cette var n'est pas dans le tableau
*/

int				catch_env_varr(char *arg, char *env_line)
{
    unsigned int i;

    i = 0;
	if (!env_line && !env_line[i])
		return (-1);
    while (arg[i] && env_line[i])
    {
        if (arg[i] != env_line[i])
            break ;
        i++;
    }
    if ((env_line[i] == '\0' || env_line[i] == '=') && i == ft_strlen(arg))
        return (0);
    return (1);
}

char			**copy_unset_tab(char **src)
{
    char **new_tab;
    int size;
    int i;
	int j;

    i = 0;
	j = 0;
    size = double_tab_size(src);
    new_tab = malloc(sizeof(char**) * (size + 1));
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
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char**) * (double_tab_size(arg) + 1));
	if (!tmp)
		malloc_error();
	while (arg[i])
	{
		if (is_valid_name(arg[i]) == -1)
		{
			ft_printf("minishell: unset: « %s » : identifiant non valable\n", arg[i]);
			i++;
		}
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

int				ft_unset(t_env *env, t_list *lst)
{
	char	**new_tab;
	int		i;
	int 	j;

	i = 0;
	j = 0;
	while (lst->tab_cmd[i])
	{
		lst->tab_cmd[i] = delete_quote(lst->tab_cmd[i]);
		i++;
	}
	i = 0;
	while (lst->tab_cmd[i])
	{
		if (is_valid_name(lst->tab_cmd[i]) == 0) 
		{
			j = 0;
			while (env->tab[j])
			{
				if (catch_env_varr(lst->tab_cmd[i], env->tab[j]) == 0)
				{
					free(env->tab[j]);
					env->tab[j] = ft_strdup("123456789");
				}
				j++;
			}
			i++;
		}
		else
		{
			ft_printf("minishell: unset: « %s » : identifiant non valable\n", lst->tab_cmd[i]);
			i++;
		}
		
	}
	new_tab = copy_unset_tab(env->tab);
	free_double_tab(env->tab);
	env->tab = copy_double_tab(new_tab);
	free_double_tab(new_tab);
	return (0);
}
