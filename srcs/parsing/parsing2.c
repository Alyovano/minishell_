/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:15:45 by user42            #+#    #+#             */
/*   Updated: 2021/01/18 11:33:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			token_to_parse_init(t_user *start)
{
	start->split_nb = 1;
	start->chevron_nb = 0;
}

int				parsing_input_verif1(char *input, t_user *start)
{
	t_quote quote;
	int		error;

	if (!(start->user_input = ft_strdup(input)))
		malloc_error();
	token_to_parse_init(start);
	error = check_input_start(start);
	if (error < 0)
	{
		error_output_token(error, NULL, '\0');
		return (-1);
	}
	error = input_to_tab(start, &quote);
	if (error < 0)
	{
		error_output_token(error, NULL, '\0');
		return (-1);
	}
	error = check_pipe(start->user_input, &quote);
	if (error < 0)
	{
		error_output_token(error, NULL, '\0');
		return (-1);
	}
	return (0);
}

int				parsing_input_verif2(t_user *start)
{
	t_quote quote;
	int		i;

	i = 0;
	if (parsing_redirrect(start) == -1)
		return (-1);
	split_pipe(start, &quote);
	while (start->user_cmd_tab[i])
		free(start->user_cmd_tab[i++]);
	if (quote.verif != 0)
	{
		error_output_token(-5, NULL, '\0');
		return (-1);
	}
	return (0);
}