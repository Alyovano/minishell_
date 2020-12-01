#include "../includes/minishell.h"

/*
** Modification de la fonction error_output_token pour permettre l'envoi de 
** chaine de caractères pour imprimer une erreur
*/

void     malloc_error(void)
{
	strerror(errno);
	exit(EXIT_FAILURE);
}

void         error_output_token(int error, char *str)
{
    if (error == -1)
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « ; »\n");
    else if (error == -2)
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « > »\n");
    else if (error == -3)
        ft_printf("Minishell cannot do that: No multilines : « < »\n");
    else if (error == -4)
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « newline »\n");
    else if (error == -5)
        ft_printf("Minishell cannot do that: No multilines\n");
    else if (error == -6)
        ft_printf("%s : commande introuvable\n", str);
    //Ici ca va free comme jaja  --> free dans minishell avant de reprendre boucle while
}