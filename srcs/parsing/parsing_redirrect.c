/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirrect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:53:39 by user42            #+#    #+#             */
/*   Updated: 2020/12/08 13:40:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Cherche les ">|" dans elem
** retourne le nombre d'éléments trouvés
** retorune 0 si existe pas
*/

int		get_redir_pipe(char *elem, t_quote *quote)
{
	int i;
	int nb;
	
	i = 0;
	nb = 0;	
	quote->token_in_simple_quote = -1;
	quote->token_in_dquote = -1;
	while (elem[i])
	{
		if (elem[i] == '\'' && (get_backslash(elem, i) == 0))
			quote->token_in_simple_quote *= -1;
		if (elem[i] == '"' && (get_backslash(elem, i) == 0))
			quote->token_in_dquote *= -1;
		if (quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1)
		{
			if (elem[i] == '>' && elem[i + 1] == '|')
				nb++;
		}
		i++;
	}
	return (nb);
}

char	*remove_redir_pipe(char *elem, t_quote *quote, int nb)
{
	int		i;
	int		j;
	char	*tmp;
	
	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(elem) - nb));
	quote->token_in_simple_quote = -1;
	quote->token_in_dquote = -1;
	while (elem[j])
	{
		tmp[i] = elem[j];
		if (elem[j] == '\'' && (get_backslash(elem, j) == 0))
			quote->token_in_simple_quote *= -1;
		if (elem[j] == '"' && (get_backslash(elem, j) == 0))
			quote->token_in_dquote *= -1;
		if (quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1)
		{
			if (elem[j] == '>' && elem[j + 1] == '|')
				j++;
		}
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int		parsing_redirrect(t_user *start)
{
	t_quote	quote;
	char	*tmp;
	int		nb_redirr_pipe;
	int		i;

	i = 0;
	while (start->user_cmd_tab[i])
	{
		//ft_printf("Before: |%s|\n", start->user_cmd_tab[i]);
		nb_redirr_pipe = get_redir_pipe(start->user_cmd_tab[i], &quote);
		if (nb_redirr_pipe > 0)
		{
			tmp = ft_strdup(start->user_cmd_tab[i]);
			free(start->user_cmd_tab[i]);
			start->user_cmd_tab[i] = remove_redir_pipe(tmp, &quote, nb_redirr_pipe);
			free(tmp);
		}
		//ft_printf("Result: |%s|\n", start->user_cmd_tab[i]);
		i++;
	}
	return (0);
}