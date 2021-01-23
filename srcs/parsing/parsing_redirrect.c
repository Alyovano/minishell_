/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirrect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:53:39 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 16:44:38 by user42           ###   ########.fr       */
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
	init_quotes(quote, -1, -1);
	while (elem[i])
	{
		if (elem[i] == '\'' && (get_backslash(elem, i) == 0))
			quote->squote *= -1;
		if (elem[i] == '"' && (get_backslash(elem, i) == 0))
			quote->dquote *= -1;
		if (quote->dquote == -1 && quote->squote == -1)
		{
			if (elem[i] == '>' && elem[i + 1] == '|')
				nb++;
		}
		i++;
	}
	return (nb);
}

char	*rm_redir_pipe(char *elem, t_quote *quote, int nb)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	tmp = malloc(sizeof(char) * (ft_strlen(elem) - nb));
	if (tmp == NULL)
		malloc_error();
	init_quotes(quote, -1, -1);
	while (elem[++j])
	{
		tmp[++i] = elem[j];
		if (elem[j] == '\'' && (get_backslash(elem, j) == 0))
			quote->squote *= -1;
		if (elem[j] == '"' && (get_backslash(elem, j) == 0))
			quote->dquote *= -1;
		if (quote->dquote == -1 && quote->squote == -1)
		{
			if (elem[j] == '>' && elem[j + 1] == '|')
				j++;
		}
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
		nb_redirr_pipe = get_redir_pipe(start->user_cmd_tab[i], &quote);
		if (nb_redirr_pipe > 0)
		{
			tmp = ft_strdup(start->user_cmd_tab[i]);
			free(start->user_cmd_tab[i]);
			start->user_cmd_tab[i] = rm_redir_pipe(tmp, &quote, nb_redirr_pipe);
			free(tmp);
		}
		i++;
	}
	return (0);
}
