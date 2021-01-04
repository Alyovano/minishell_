/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2020/10/22 13:20:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Fonction pour calculer le nombre de backslash qu'il y a
** avant le quote actuel. Retourne modulo 2 du nombre de backslash
** si == 1 (quote printable) si == 0 (quote pour string)
** ex. echo He\llo\\" => 0 | ex. echo He\llo\\\" => 1
*/

int		get_backslash(char *str, int i)
{
	int nb_backslash;

	nb_backslash = 0;
	while (str[--i] && str[i] == '\\')
		nb_backslash++;
	return (nb_backslash % 2);
}
