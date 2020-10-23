/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:54:49 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 13:02:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Funcion to check end of line
** minishell> echo | ; --> bash: erreur de syntaxe près du symbole inattendu « ; »
** minishell> echo | --> on ne gère pas les multi-lignes
*/
int		check_pipe(char **str)
{
	(void)str;
	ft_printf("Check pipe !\n");
	return (1);
}
