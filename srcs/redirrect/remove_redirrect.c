/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirrect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:10:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 13:11:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_redirrect3(char *str, char **ret, int *j, int *i)
{
	t_quote *quote;

	quote = malloc(sizeof(t_quote));
	if (!quote)
		malloc_error();
	else if (((str[*i] == '>' || str[*i] == '<') && get_backslash(str, *i) \
					== 0 && (str[*i + 1] != '>' && str[*i + 1] != '<')))
	{
		*i += next_redirrect(str, *i + 1, quote);
		(*i)++;
		while (str[*i] == ' ')
			(*i)++;
	}
	else if (((str[*i] == '>' || str[*i] == '<') && get_backslash(str, *i) \
					== 0 && (str[*i + 1] == '>' || str[*i + 1] == '<')))
	{
		*i += next_redirrect(str, *i + 2, quote);
		*i += 2;
		while (str[*i] == ' ')
			(*i)++;
	}
	else
		(*ret)[(*j)++] = str[(*i)++];
	free(quote);
}

void	remove_redirrect2(char *str, char **ret, int *j, int *i)
{
	if (str[*i] == '\'' && get_backslash(str, *i) == 0)
	{
		(*ret)[(*j)++] = str[(*i)++];
		while (str[*i] && !(str[*i] == '\'' && get_backslash(str, *i) == 0))
			(*ret)[(*j)++] = str[(*i)++];
		if (str[*i] == '\'')
			(*ret)[(*j)++] = str[(*i)++];
	}
	else if (str[*i] == '"' && get_backslash(str, *i) == 0)
	{
		(*ret)[(*j)++] = str[(*i)++];
		while (str[*i] && !(str[*i] == '"' && get_backslash(str, *i) == 0))
			(*ret)[(*j)++] = str[(*i)++];
		if (str[*i] == '"')
			(*ret)[(*j)++] = str[(*i)++];
	}
	else
		remove_redirrect3(str, ret, j, i);
}

char	*remove_redirrect(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * ft_strlen(str));
	if (!ret)
		malloc_error();
	while (str[i])
	{
		remove_redirrect2(str, &ret, &j, &i);
	}
	ret[j] = '\0';
	return (ret);
}
