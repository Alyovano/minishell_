/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_quote_actuel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:23:38 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 14:37:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Retourne la taille de la quote
** stock dans quote->verif si elle est valide
** Si quote->len vaut -1 :
** - Alors la quote a ete slm ouverte et est invalide
** Si la quote->len vaut 1:
** Alors c'est une quote vide type "" ou ''
** Si quote->len > 1 :
** Je considere qu'il y a du texte recuperable dans la quote
*/

void	init_quote_len_validity(t_quote *quote)
{
	quote->len = 0;
	quote->verif = 0;
}

int		quote_get_len_and_validity(t_user *start, t_quote *quote, int i)
{
	init_quote_len_validity(quote);
	while (start->user_input[i]
	&& (quote->squote % 2 != 0 || quote->dquote % 2 != 0))
	{
		if (start->user_input[i] == '"')
		{
			if (get_backslash(start->user_input, i) == 0 && \
										quote->squote % 2 == 0)
				quote->dquote++;
		}
		else if (start->user_input[i] == '\'')
		{
			if (quote->squote % 2 == 0 && quote->dquote % 2 == 0)
			{
				if (get_backslash(start->user_input, i) == 0)
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

int		quote_len(char *str)
{
	int		i;
	char	quote;

	i = 1;
	quote = *str;
	while (str[i])
	{
		if (str[i] == quote && get_backslash(str, i) == 0)
		{
			break ;
		}
		i++;
	}
	return (i);
}

char	*delete_quote(char *str)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (tmp == NULL)
		malloc_error();
	while (str[i])
	{
		while (str[i] == '"' || str[i] == '\'')
			i++;
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}
