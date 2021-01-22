/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2021/01/22 15:16:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				input_to_tab_verif(t_user *start, t_quote *quote, int i)
{
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
	return (i);
}

int				input_to_tab(t_user *start, t_quote *quote)
{
	int i;

	i = 0;
	while (start->user_input[i])
	{
		quote->squote = 0;
		quote->dquote = 0;
		i = input_to_tab_verif(start, quote, i);
		if (is_this_splitable(start, quote, i) == -1)
			return (-1);/*
		if (is_this_redirectable(start, quote, i) == -1)
			return (-2);
		if (is_this_redirectable_reverse(start, quote, i) == -1)
			return (-3);*/
		i++;
	}
	return (0);
}

int				parsing_input(char *input, t_user *start, t_env *env)
{
	t_quote quote;
	int		i;

	i = 0;
	(void)env;
	start->to_free = 0;
	if (!input || !*input)
		return (0);
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (-1);
	if (parsing_input_verif1(input, start) == -1)
		return (-1);
	first_split_dirty_line(start, &quote);
	clean_line(start, &quote);
	if (parsing_input_verif2(start) == -1)
		return (-1);
	return (0);
}
