/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_redirrect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:26:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 11:28:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		next_redirrect2(int *i, int *j, char *str, t_quote **q)
{
	if ((*q)->dquote == 1 && str[*i] == '"' && get_backslash(str, *i) == 0)
	{
		(*q)->dquote *= -1;
		(*j)++;
		if (str[++(*i) + 1] == ' ' || str[*i + 1] == '\0')
			return (*j);
	}
	else if ((*q)->squote == 1 && str[*i] == '\'' && \
											get_backslash(str, *i) == 0)
	{
		(*q)->squote *= -1;
		(*j)++;
		if (str[++(*i) + 1] == ' ' || str[*i + 1] == '\0')
			return (*j);
	}
	else if ((*q)->dquote == -1 && (*q)->squote == -1 \
		&& str[*i] == ' ')
		return (*j);
	else
	{
		(*i)++;
		(*j)++;
	}
	return (-1);
}

void	next_redirrect_init(int *j, int *i, char *str, t_quote **q)
{
	*j = 0;
	(*q)->dquote = -1;
	(*q)->squote = -1;
	while (str[*i] && str[*i] == ' ')
	{
		(*i)++;
		(*j)++;
	}
}

int		next_redirrect(char *str, int i, t_quote *q)
{
	int		j;

	next_redirrect_init(&j, &i, str, &q);
	while (str[i])
	{
		if (q->dquote == -1 && q->squote == -1 \
			&& (str[i] == '\'' || str[i] == '"') && get_backslash(str, i) == 0)
		{
			if (str[i] == '\'')
				q->squote *= -1;
			else
				q->dquote *= -1;
			i++;
			j++;
		}
		else
		{
			if (next_redirrect2(&i, &j, str, &q) != -1)
				return (j);
		}
	}
	return (j);
}
