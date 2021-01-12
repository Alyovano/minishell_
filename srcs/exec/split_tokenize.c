/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:12:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 15:29:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function to count number of splitable spaces to maloc tab after
*/

void	is_split_tokenize(t_user *start, int i)
{
	if (start->user_input[i] == ' ')
	{
		if (get_backslash(start->user_input, i) == 0)
			start->split_nb++;
	}
}

/*
** COPY FROM SPLIT DIRTY LINE but maybe split == " "
*/

int		maybe_split_tokenize(t_user *start, int i)
{
	if (start->user_input[i] == ' ')
	{
		if (get_backslash(start->user_input, i) == 0)
			return (0);
	}
	return (1);
}

void	cut_input_to_tab_tokenize2(int *i, t_user *start, t_quote *q)
{
	if (start->user_input[*i] == '\'' && \
					(get_backslash(start->user_input, *i) == 0))
	{
		q->squote = 1;
		quote_get_len_and_validity(start, q, *i + 1);
		(*i) += q->len;
		q->squote = 0;
	}
	if (start->user_input[*i] == '"'
	&& (get_backslash(start->user_input, *i) == 0))
	{
		q->dquote = 1;
		quote_get_len_and_validity(start, q, *i + 1);
		(*i) += q->len;
		q->dquote = 0;
	}
}

int		cut_input_to_tab_tokenize(t_user *start, t_quote *quote)
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
		cut_input_to_tab_tokenize2(&i, start, quote);
		if (maybe_split_tokenize(start, i) == 0)
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

/*
** Splits every element in lst->content
** Return double tab
** tab_cmd[0] --> builtin
** tab_cmd[1] --> flag
** tab_cmd[n] --> argu
*/

char	split_tokenize(t_user *start, t_quote *quote)
{
	if (init_double_tab_cmd(start) == -1)
		return (-1);
	cut_input_to_tab_tokenize(start, quote);
	return (0);
}
