/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 10:49:03 by user42           ###   ########.fr       */
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
			return (-1);
		if (is_this_redirectable(start, quote, i) == -1)
			return (-2);
		if (is_this_redirectable_reverse(start, quote, i) == -1)
			return (-3);
		i++;
	}
	return (0);
}

void			token_to_parse_init(t_user *start)
{
	start->split_nb = 1;
	start->chevron_nb = 0;
}

int				parsing_input(char *input, t_user *start, t_env *env)
{
	int		error;
	t_quote *quote;

	if (!input || !*input)
		return (0);
	if (!(quote = malloc(sizeof(quote))))
		malloc_error();
	if (!(start->user_input = ft_strdup(input)))
		malloc_error();
	token_to_parse_init(start);
	error = check_input_start(start);
	if (error < 0)
	{
		free(quote);
		error_output_token(error, NULL, '\0');
		return (-1);
	}
	error = input_to_tab(start, quote);
	if (error < 0)
	{
		free(quote);
		error_output_token(error, NULL, '\0');
		return (-1);
	}
	error = check_pipe(start->user_input, quote);
	if (error < 0)
	{
		free(quote);
		error_output_token(error, NULL, '\0');
		return (-1);
	}
	first_split_dirty_line(start, quote);
	clean_line(start, quote);
	add_environnement_var(start, quote, env);
	if (parsing_redirrect(start) == -1)
	{
		free(quote);
		return (-1);
	}
	split_pipe(start, quote);
	if (quote->verif != 0)
	{
		free(quote);
		error_output_token(-5, NULL, '\0');
		return (-1);
	}
	free(quote);
	return (0);
}
