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
** return (-1)
** erreur critique, bash arrete tout dans ce cas
** il faudra evidemment sortir proprement ici
*/

int			check_semicolon_validity(t_user *start, int i)
{
	while (start->user_input[i] && start->user_input[i] == ' ')
		i++;
	if (start->user_input[i] == ';')
	{
		return (-1);
	}
	return (0);
}

/*
** Si split_nb == -1 ca veut dire qu'on arrete tout pour cette ligne de cmd
*/

int			is_this_splitable(t_user *start, t_quote *quote, int i)
{
	(void)quote;
	if (start->user_input[i] == ';')
	{
		if (get_backslash(start->user_input, i) == 0)
		{
			if (check_semicolon_validity(start, i + 1) == -1)
			{
				start->split_nb = -1;
				return (-1);
			}
			else
			{
				start->split_nb++;
				return (0);
			}
		}
	}
	return (1);
}
