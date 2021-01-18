/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:53:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/18 12:54:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_str_n_dup(const char *s1, int size)
{
	size_t	longueur;
	char	*tab;

	longueur = size + 1;
	tab = malloc(sizeof(char) * longueur);
	if (tab == NULL)
		malloc_error();
	ft_strlcpy(tab, s1, longueur);
	return (tab);
}

void		init_quotes(t_quote *quote, int squote, int dquote)
{
	quote->squote = squote;
	quote->dquote = dquote;
}

void		init_quotes_to_fix(t_quote *quote)
{
	quote->verif = 0;
	quote->squote = 0;
	quote->dquote = 0;
}
