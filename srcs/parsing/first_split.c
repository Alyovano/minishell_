/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 10:49:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_str_n_dup(const char *s1, int size)
{
	size_t	longueur;
	char	*tab;

	longueur = size + 1;
	tab = malloc(sizeof(char) * longueur);
	if (tab == NULL)
		malloc_error();
	ft_strlcpy(tab, s1, longueur);
	return (tab);
}

int			init_double_tab_cmd(t_user *start)
{
	int i;

	i = 0;
	start->user_cmd_tab = malloc(sizeof(start->user_cmd_tab)
					* (start->split_nb + 1));
	if (!start->user_cmd_tab)
		malloc_error();
	while (i < start->split_nb + 1)
	{
		start->user_cmd_tab[i] = 0;
		i++;
	}
	return (0);
}

int			maybe_split(t_user *start, int i)
{
	if (start->user_input[i] == ';')
	{
		if (get_backslash(start->user_input, i) == 0)
			return (0);
	}
	return (1);
}

/*
** FIX
** Il faudra tout reverifier encore une fois, ligne par ligne
** directement a l'interieur du tableau, des erreurs peuvent encore passer
** + norme |!|
*/

void			init_quotes_to_fix(t_quote *quote)
{
	quote->verif = 0;
	quote->squote = 0;
	quote->dquote = 0;
}

int				cut_input_to_tab(t_user *start, t_quote *quote)
{
	int k;
	int i;
	int j;

	k = 0;
	i = 0;
	j = 0;
	while (start->user_input[i])
	{
		init_quotes_to_fix(quote);
		if (start->user_input[i] == '\''
		&& (get_backslash(start->user_input, i) == 0))
		{
			quote->squote = 1;
			quote_get_len_and_validity(start, quote, i + 1);
			i += quote->len;
			quote->squote = 0;
		}
		if (start->user_input[i] == '"'
		&& (get_backslash(start->user_input, i) == 0))
		{
			quote->dquote = 1;
			quote_get_len_and_validity(start, quote, i + 1);
			i += quote->len;
			quote->dquote = 0;
		}
		if (maybe_split(start, i) == 0)
		{
			start->user_cmd_tab[k] = ft_str_n_dup(start->user_input + j, i - j);
			k++;
			j = i;
		}
		i++;
	}
	if (start->user_input[i] == 0 && quote->verif == 0)
	{
		start->user_cmd_tab[k] = ft_str_n_dup(start->user_input + j, i - j);
		k++;
	}
	return (0);
}

int				first_split_dirty_line(t_user *start, t_quote *quote)
{
	init_double_tab_cmd(start);
	cut_input_to_tab(start, quote);
	return (0);
}
