#include "libft.h"

void    free_double_tab(char **tab)
{
    int i;

    i = 0;
    while (*tab && tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}