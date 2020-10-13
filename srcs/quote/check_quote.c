/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:24:39 by user42            #+#    #+#             */
/*   Updated: 2020/10/13 10:24:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Fonction pour calculer le nombre de backslash qu'il y a 
** avant le quote actuel. Retourne modulo 2 du nombre de backslash
** si == 1 (quote printable) si == 0 (quote pour string)
** ex. echo He\llo\\" => 0 | ex. echo He\llo\\\" => 1
*/
int		get_backslash(char *str)
{
	int nb_backslash;
	int i;
	
	i = 0;
	nb_backslash = 0;
	while (str[--i] && str[i] == '\\')
		nb_backslash++;
	return (nb_backslash % 2);
}

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
			return (i); //erreur faux positif, il faut retourner fail ou ok
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
	while (start->user_input[++i])
	{
		printf("%c\n", start->user_input[i]);
		if ((start->user_input[i] == '\'' || start->user_input[i] == '"')\
							&& (get_backslash(start->user_input + i) == 0))
		{
			ft_printf("checking quotes\n");
			if (i += is_valid_quote(start->user_input + i) == FAIL)
				return (FAIL);
			else
			{
				 //i += is_valid_quote(start->user_input + i);
			}
				
		}
		//ft_printf("No quote checking needed\n");
	}
	return (OK);
}