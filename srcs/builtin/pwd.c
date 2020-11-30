#include "../includes/minishell.h"

/*
**Si buf est NULL lors de l'appel. 
**Dans ce cas, le tampon alloué a la longueur size à moins que size soit égal à zéro,
**auquel cas buf est alloué avec la taille nécessaire.
**Il est possible (et même fortement conseillé) de libérer le tampon avec free(3).
*/

int         ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		malloc_error();
	ft_printf("%s\n", tmp);
	free(tmp);
    return (0);
}