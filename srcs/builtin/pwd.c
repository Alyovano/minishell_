/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:55:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**Si buf est NULL lors de l'appel. 
**Dans ce cas, le tampon alloué a la longueur size à moins que size soit égal à zéro,
**auquel cas buf est alloué avec la taille nécessaire.
**Il est possible (et même fortement conseillé) de libérer le tampon avec free(3).
*/

int         ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		malloc_error();
	ft_printf("%s\n", tmp);
	free(tmp);
    return (0);
}