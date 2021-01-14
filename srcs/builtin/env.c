/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:55:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** env ne fait que print les var qui ont une valeur assignee
** il peut aussi en ajouter ex
**         $ env lol=56
** ensuite il print le tableau
** les valeurs ajoutees par l'apl de env sont detruite apres le print
*/

int			have_value(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int			ft_env(t_env *env, t_list *lst)
{
	int i;

	(void)lst;
	i = 0;
	while (env->tab[i])
	{
		env->tab[i] = delete_quote(env->tab[i]);
		if (have_value(env->tab[i]) == 1)
			ft_printf("%s\n", env->tab[i]);
		i++;
	}
	return (0);
}
