#include "../includes/minishell.h"

void        error_output_token(t_user *start, int error)
{
    (void)start;
    if (error == -1)
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « ; »\n");
    else if (error == -2)
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « > »\n");
    else if (error == -3)
        ft_printf("Minishell cannot do that: No multilines : « < »\n");
    else if (error == -4)
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « newline »\n");
    //Ici ca va free comme jaja
}