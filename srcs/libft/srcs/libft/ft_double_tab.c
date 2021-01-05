/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 10:49:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Compte la taille d'un tableau 2 dimm
*/

int			double_tab_size(char **src)
{
	int i;

	i = 0;
	while (src[i] != 0)
		i++;
	return (i);
}

/*
** Copy le tableau source dans un nouveau tableau (2D)
** Return un pointeur sur le nouveau tableau
*/

char		**copy_double_tab(char **src)
{
	char	**new_tab;
	int		size;
	int		i;

	i = 0;
	size = double_tab_size(src);
	new_tab = malloc(sizeof(char**) * (size + 1));
	if (!new_tab)
		malloc_error();
	new_tab[size] = 0;
	while (src[i])
	{
		new_tab[i] = ft_strdup(src[i]);
		i++;
	}
	return (new_tab);
}
