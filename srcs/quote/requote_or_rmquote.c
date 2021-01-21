/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requote_or_rmquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 14:25:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		init_requote_str(t_requote_str *trs, char *str)
{
	trs->new = malloc((sizeof(char) * (ft_strlen(str)) + 3));
	if (trs->new == NULL)
		malloc_error();
	trs->i = 0;
	trs->j = 0;
	trs->token = 0;
}

/*
** Malloc +3 pcq strlen + 1 et +2 pour les 2 quotes
*/

char		*requote_str(char *str)
{
	t_requote_str	trs;

	init_requote_str(&trs, str);
	while (str[trs.i])
	{
		trs.new[trs.i + trs.j] = str[trs.i];
		if (trs.token == 0 && str[trs.i] == '=')
		{
			trs.token = 1;
			trs.j = 1;
			trs.new[trs.i + trs.j] = '"';
		}
		trs.i++;
	}
	if (trs.token == 1)
	{
		trs.new[trs.i + trs.j] = '"';
		trs.new[trs.i + trs.j + 1] = 0;
	}
	else
		trs.new[trs.i] = 0;
	free(str);
	return (trs.new);
}

void		requote_arg(t_list *lst)
{
	int i;

	i = 0;
	while (lst->tab_cmd[i])
	{
		lst->tab_cmd[i] = delete_quote(lst->tab_cmd[i]);
		lst->tab_cmd[i] = requote_str(lst->tab_cmd[i]);
		i++;
	}
}
