#include "libft.h"

/*
** Compte la taille d'un tableau 2 dimm
*/

int     double_tab_size(char **src)
{
    int i;

    i = 0;
    while (src[i] != 0)
        i++;
    return (i);
}

/*
** Copy le tableau source dans un nouveau tableau (2D)
** Return un pointeur sur le nouveau tableau
*/

char    **copy_double_tab(char **src)
{
    char **new_Tab;
    int size;
    int i;

    i = 0;
    size = double_tab_size(src);
    new_Tab = malloc(sizeof(char**) * (size + 1));
    new_Tab[size] = 0;
    while (src[i])
    {
        new_Tab[i] = ft_strdup(src[i]);
        i++;
    }
    printf("SIZE = %d\n", size);
    return (new_Tab);
}
