/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:24:39 by user42            #+#    #+#             */
/*   Updated: 2020/10/12 16:53:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Fonction similaire à check_quote_number mais pas du tout terminée
*/
int		is_valid_quote(char *str)
{
	int		i;
	char	type;

	i = 0;
	type = str[i];
	while (str[++i])
	{
		if (str[i] == type)
			return (i);
		//if (type == '"' && str[i] == '\'' && str[i - 1] != "\\")
			//quote in another quote
		i++; //no quote
	}
	return (OK);

}

/* (check_quote)
** Fonction pour vérifier si la string qu'on a recu en argument est bien
** valide au niveau du nombre et l'imbrication des quotes.
** Si la quote est affichée (ex. echo \" Hello\") elle ne doit pas ^etre
** prise en compte.
*/
int		check_quote(t_user *start)
{
	int		i;

	i = -1;
	while (start->user_input[i])
	{
		i++;
		if ((start->user_input[i] == '\'' || start->user_input[i] == '"')\
									&& start->user_input[i - 1] != '\\')
		{
			if (is_valid_quote(start->user_input + i) == FAIL)
				return (FAIL);
			else
				i += is_valid_quote(start->user_input + i);			
		}
	}
	return (OK);
}