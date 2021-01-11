/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:46:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/11 15:26:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Go trough every element of list
** clean quote if needed
*/

void	check_flags(t_list *lst)
{
	int		i;

	while (lst)
	{
		i = 1;
		while (lst->tab_cmd[i] && (lst->tab_cmd[i][0] == '-' || \
		((lst->tab_cmd[i][0] == '"' || lst->tab_cmd[i][0] == '\'') \
									&& lst->tab_cmd[i][1] == '-')))
		{
			clean_quote(&lst->tab_cmd[i]);
			i++;
		}
		lst = lst->next;
	}
}
