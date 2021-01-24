/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:28:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 15:30:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** remplace $? par la valeur de retour precedente
** Retourne la taille de la valeur de $?
*/

int		prev_return_value(t_list *lst, int i, int j, t_dollar *dol)
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
