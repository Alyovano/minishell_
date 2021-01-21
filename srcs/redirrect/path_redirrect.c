/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_redirrect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:36:15 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 13:42:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_file_return(int j, char *tmp)
{
	tmp[j] = '\0';
	return (tmp);
}

void	get_file_init(int *j, char **tmp, t_quote *q, char *str)
{
	*j = 0;
	q->dquote = -1;
	q->squote = -1;
	*tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(*tmp))
		malloc_error();
}

void	get_file_quote(char *str, int *i, t_quote **q)
{
	if ((*q)->dquote == -1 && (*q)->squote == -1 \
		&& (str[*i] == '\'' || str[*i] == '"') && get_backslash(str, *i) == 0)
	{
		if (str[(*i)++] == '\'')
			(*q)->squote *= -1;
		else
			(*q)->dquote *= -1;
	}
}

char	*get_file(char *str, int i, int j, t_quote *q)
{
	char	*tmp;

	get_file_init(&j, &tmp, q, str);
	while (str[i])
	{
		get_file_quote(str, &i, &q);
		if (q->dquote == 1 && str[i] == '"' && get_backslash(str, i) == 0)
		{
			q->dquote *= -1;
			if (str[++i] == ' ' || str[i] == '\0')
				return (get_file_return(j, tmp));
		}
		else if (q->squote == 1 && str[i] == '\'' && get_backslash(str, i) == 0)
		{
			q->squote *= -1;
			if (str[++i] == ' ' || str[i] == '\0')
				return (get_file_return(j, tmp));
		}
		else if (q->dquote == -1 && q->squote == -1 \
			&& (str[i] == ' ' || str[i] == '>' || str[i] == '<'))
			return (get_file_return(j, tmp));
		else
			tmp[j++] = str[i++];
	}
	return (get_file_return(j, tmp));
}
