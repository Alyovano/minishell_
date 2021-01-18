/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:25:55 by user42            #+#    #+#             */
/*   Updated: 2021/01/18 12:51:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Same function as maybe_split,
** but str[i] == ';' is replaced with '|'
*/

static int		maybe_split(char *str, int i)
{
	if (str[i] == '|')
	{
		if (get_backslash(str, i) == 0)
			return (0);
	}
	return (1);
}

/*
** Same function as quote_get_len_and_validity,
** but t_user *start is replaced by char *str
*/

static int		quote_get_len_and_validity2(char *str, t_quote *quote, int i)
{
	quote->len = 0;
	quote->verif = 0;
	while (str[i]
	&& (quote->squote % 2 != 0 || quote->dquote % 2 != 0))
	{
		if (str[i] == '"')
		{
			if (get_backslash(str, i) == 0 && quote->squote % 2 == 0)
				quote->dquote++;
		}
		else if (str[i] == '\'')
		{
			if (quote->squote % 2 == 0 && quote->dquote % 2 == 0)
			{
				if (get_backslash(str, i) == 0)
					quote->squote++;
			}
			else if (quote->squote % 1 == 0 && quote->dquote % 2 == 0)
				quote->squote++;
		}
		i++;
		quote->len++;
	}
	quote->verif = (quote->dquote % 2) + (quote->squote % 2);
	return (quote->len - 1);
}

void			cut_to_tab_quotes(t_quote *quote, char *str, int *i)
{
	init_quotes_to_fix(quote);
	if (str[*i] == '\''
	&& (get_backslash(str, *i) == 0))
	{
		quote->squote = 1;
		quote_get_len_and_validity2(str, quote, *i + 1);
		*i += quote->len;
		quote->squote = 0;
	}
	if (str[*i] == '"'
	&& (get_backslash(str, *i) == 0))
	{
		quote->dquote = 1;
		quote_get_len_and_validity2(str, quote, *i + 1);
		*i += quote->len;
		quote->dquote = 2;
	}
}

t_list			*cut_input_to_tab_pipe2(t_int_pack *pack, char *str, t_quote *q)
{
	char		*temp;
	t_list		*cmd;

	while (str[pack->i])
	{
		cut_to_tab_quotes(q, str, &pack->i);
		if (maybe_split(str, pack->i) == 0)
		{
			temp = ft_str_n_dup(str + pack->j, pack->i - pack->j);
			if (pack->k == 0)
				cmd = ft_lstnew(temp);
			else
				ft_lstadd_back(&cmd, ft_lstnew(temp));
			(pack->k)++;
			pack->j = pack->i + 1;
			if (str[pack->j + 1] == ' ')
				(pack->j)++;
		}
		(pack->i)++;
	}
	return (cmd);
}

/*
** Same function as cut_input_to_tab,
** but t_user *start is replaced by char *str
** a t_list cmd is created in place of char **tab for previus split
*/

t_list			*cut_input_to_tab_pipe(t_quote *quote, char *str)
{
	t_list		*cmd;
	char		*temp;
	t_int_pack	pack;

	pack.k = 0;
	pack.i = 0;
	pack.j = 0;
	cmd = cut_input_to_tab_pipe2(&pack, str, quote);
	if (str[pack.i] == 0 && quote->verif == 0)
	{
		temp = ft_str_n_dup(str + pack.j, pack.i - pack.j);
		if (pack.k == 0)
			cmd = ft_lstnew(temp);
		else
			ft_lstadd_back(&cmd, ft_lstnew(temp));
	}
	return (cmd);
}
