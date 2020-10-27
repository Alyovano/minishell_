/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:54:49 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 11:51:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Funcion to check end of line
** minishell> echo | ; --> bash: erreur de syntaxe près du symbole inattendu « ; »
** minishell> echo | --> on ne gère pas les multi-lignes
*/

int		check_pipe(char *str, t_quote *quote)
{
	int i;

	i = 0;
	quote->token_in_simple_quote = -1;
	quote->token_in_dquote = -1;
	while (str[i])
	{
		if (str[i] == '\'' && (get_backslash(str, i) == 0))
			quote->token_in_simple_quote *= -1;
		if (str[i] == '"' && (get_backslash(str, i) == 0))
			quote->token_in_dquote *= -1;
		if (quote->token_in_simple_quote == -1 && quote->token_in_dquote == -1)
		{
			if (str[i] == '|')
			{
				i++;
				while (str[i] == ' ')
					i++;
				if (str[i] == ';')
					return (-1);
				if (str[i] == '\0')
					return (-5);
			}
		}
		i++;
	}
	return (1);
}
