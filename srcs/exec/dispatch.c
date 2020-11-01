/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2020/11/01 10:41:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Fonction qui va dispatch après notre dernier split vers l'exécution
*/

int		dispatch_cmd(t_list *lst)
{
	/*
	if (valid_and_clean_builtin(lst) == 1)
	{
		ft_printf("Valid builtin !\n");
	}
	else
	{
		//return good error with builtin arg
		ft_printf("Error builtin !\n");
	}
	*/
	parse_flags(lst);
	
	return (1);
}