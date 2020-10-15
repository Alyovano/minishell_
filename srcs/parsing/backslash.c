#include "../includes/minishell.h"

/*
** Fonction pour calculer le nombre de backslash qu'il y a 
** avant le quote actuel. Retourne modulo 2 du nombre de backslash
** si == 1 (quote printable) si == 0 (quote pour string)
** ex. echo He\llo\\" => 0 | ex. echo He\llo\\\" => 1
*/

int		get_backslash(char *str, int i)
{
	int nb_backslash;

	nb_backslash = 0;
	while (str[--i] && str[i] == '\\')
		nb_backslash++;
	return (nb_backslash % 2);
}