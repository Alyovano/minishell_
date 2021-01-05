/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:46:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 14:50:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Fonction pour vérifier s'il y a un flag valable dans argu
** ne vérifie pas le flag en lui-meme mais la syntaxe
** il faut pas d'espaces dans les flags et un '-' au début d'argu
*/

int		valid_flags(char *argu, int *i)
{
	t_quote	*quote;

	quote = malloc(sizeof(t_quote));
	if (!quote)
		exit(-1);
	quote->squote = -1;
	quote->dquote = -1;
	if (!((argu[*i] == '-' && argu[*i + 1] != ' ') || (argu[*i] == '\'' && \
		argu[*i + 1] == '-') || (argu[*i] == '"' && argu[*i + 1] == '-')))
		return (0);
	while (argu[*i])
	{
		if (argu[*i] == '\'' && (get_backslash(argu, *i) == 0))
			quote->squote *= -1;
		if (argu[*i] == '"' && (get_backslash(argu, *i) == 0))
			quote->dquote *= -1;
		if ((quote->squote == 1 || quote->dquote == 1) \
									&& argu[*i] == ' ')
			return (0);
		if ((quote->squote == -1 && quote->dquote == -1) \
									&& (argu[*i] == ' ' || argu[*i] == '\0'))
			return (1);
		(*i)++;
	}
	return (1);
}

/*
** Go trough every element of list
** check if valid flags in argu
*/

void	parse_flags(t_list *lst)
{
	int		i;
	char	*tmp;

	while (lst)
	{
		i = 0;
		if (valid_flags(lst->argu, &i) == 1)
		{
			lst->flag = ft_str_n_dup(lst->argu, i);
			clean_quote(&lst->flag);
			tmp = ft_substr(lst->argu, i + 1, ft_strlen(lst->argu));
			free(lst->argu);
			lst->argu = tmp;
		}
		lst = lst->next;
	}
}
