/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 08:11:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		next_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

int			check_redirrections(char *str, t_quote *q)
{
	int i;

	i = -1;
	init_quotes(q, -1, -1);
	while (str[++i])
	{
		if (str[i] == '"' && get_backslash(str, i) == 0)
			q->dquote *= -1;
		else if (str[i] == '\'' && get_backslash(str, i) == 0)
			q->squote *= -1;
		else if (q->squote == -1 && q->dquote == -1)
		{
			if (str[i] == '>' || str[i] == '<')
			{
				i++;
				next_spaces(str, &i);
				if (str[i] == ';' || str[i] == '|')
				{
					error_output_token(-7, NULL, str[i]);
					return (-1);
				}
			}
		}
	}
	return (0);
}

int			check_semicolon2(char *str, int *i)
{
	if (str[*i] == ';')
	{
		(*i)++;
		next_spaces(str, i);
		if (str[*i] == ';')
		{
			error_output_token(-7, ";;", '\0');
			return (-1);
		}
		else if (str[*i] == '|')
		{
			error_output_token(-7, NULL, '|');
			return (-1);
		}
	}
	return (0);
}

int			check_semicolon(char *str, t_quote *q)
{
	int i;

	i = -1;
	init_quotes(q, -1, -1);
	while (str[++i])
	{
		if (str[i] == '"' && get_backslash(str, i) == 0)
			q->dquote *= -1;
		else if (str[i] == '\'' && get_backslash(str, i) == 0)
			q->squote *= -1;
		else if (q->squote == -1 && q->dquote == -1)
		{
			if (check_semicolon2(str, &i) == -1)
				return (-1);
		}
	}
	return (0);
}

int			check_input_start(t_user *start)
{
	int		i;

	i = 0;
	while (start->user_input[i] && start->user_input[i] == ' ')
		i++;
	if (start->user_input[i] == ';')
		return (-1);
	return (0);
}
