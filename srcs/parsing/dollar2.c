/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:37:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/18 14:41:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		simple_quote_get_len_and_validity(t_user *start,
								t_quote *quote, int i, int j)
{
	quote->len = 0;
	while (start->user_cmd_tab[i][j]
	&& (quote->squote % 2 != 0 || quote->dquote % 2 != 0))
	{
		if (start->user_cmd_tab[i][j] == '"')
		{
			if (get_backslash(start->user_cmd_tab[i], j) == 0
			&& quote->squote % 2 == 0)
				quote->dquote++;
		}
		else if (start->user_cmd_tab[i][j] == '\'')
		{
			if (quote->squote % 2 == 0 && quote->dquote % 2 == 0)
			{
				if (get_backslash(start->user_cmd_tab[i], j) == 0)
					quote->squote++;
			}
			else if (quote->squote % 1 == 0 && quote->dquote % 2 == 0)
				quote->squote++;
		}
		j++;
		quote->len++;
	}
	return (quote->len - 1);
}

/*
**  ce token (quote->dollar_quote) permet de savoir
**  si on est pas deja dans une doucle quote
**	pcq si c'est le cas meme entre simple quote, il faudrait afficher
**	la var d'envi --- exemple de piege possible
**	input> " '$USER' "
**	output> "'alyovano'"
*/

int		free_dol(t_dollar *dol, char *one, char *two)
{
	if (dol->var_content)
		free(dol->var_content);
	if (dol->before_str)
		free(dol->before_str);
	if (dol->after_str)
		free(dol->after_str);
	if (one)
		free(one);
	if (two)
		free(two);
	return (0);
}

int		check_simple_quote(t_user *start, t_quote *q, int j, int i)
{
	if (start->user_cmd_tab[i][j] == '\''
	&& (get_backslash(start->user_cmd_tab[i], j) == 0)
	&& q->dollar_quote % 2 == 0)
	{
		q->squote = 1;
		simple_quote_get_len_and_validity(start, q, i, j + 1);
		j += q->len;
		q->squote = 0;
	}
	if (start->user_cmd_tab[i][j] == '"'
	&& (get_backslash(start->user_cmd_tab[i], j) == 0))
	{
		q->dollar_quote += 1;
	}
	return (j);
}

int		str_check(char *str_envi, char *to_catch)
{
	int i;
	int len;
	int check;

	i = 0;
	check = 0;
	len = ft_strlen(to_catch);
	while (i < len)
	{
		if (to_catch[i] == str_envi[i])
		{
			check++;
		}
		i++;
	}
	if (check == len && str_envi[i] == '=')
		return (0);
	return (1);
}
