/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 10:11:18 by user42           ###   ########.fr       */
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

/*
** function to check backslash in end of lst->tab[i]
*/

int			check_backslash(t_list *start)
{
	int		i;
	int		j;
	t_list	*lst;

	while (start)
	{
		lst = start->content;
		while (lst->next != NULL)
			lst = lst->next;
		i = double_tab_size(lst->tab_cmd) - 1;
		j = ft_strlen(lst->tab_cmd[i]);
		while (lst->tab_cmd[i][--j] && (lst->tab_cmd[i][j] == ' ' \
											|| lst->tab_cmd[i][j] == '\\'))
		{
			if (lst->tab_cmd[i][j] == '\\' && \
								get_backslash(lst->tab_cmd[i], j + 1) == 1)
				return (-1);
			else if (lst->tab_cmd[i][j] == '\\')
				break ;
		}
		start = start->next;
	}
	return (0);
}
