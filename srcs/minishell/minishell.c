#include "../includes/minishell.h"

/*
** Je commence le debut du parsing sous l'appel de GNL
** On attend l'input, on l'envoie dans le parseur
*/

int     minishell_loop(t_user *start)
{
    char *user_input;
    while (1)
    {
        ft_printf("minishell> ");
        get_next_line(0, &user_input);
        parsing_input(user_input, start); // Je bosse dans cet appel ./parsing/parsing.c
        conditionning(start);
        //execution(start);
        free(user_input); // Faudra tout free, pas que input
    }
    return (0);
}

/*
** LE MAIN : 
** Malloc notre structure ;
** Copie le tableau environnemental
** Appele la boucle infinie du minishell
*/

int     main(int argc, char **argv, char **env)
{
    t_user *start;

    (void) argc;
    (void) argv;
    if (!(start = malloc(sizeof(start))))
        return (-1);
    start->user_env = copy_double_tab(env);
    if (!start->user_env)
    {
        free(start);
        return (-1);
    }
    minishell_loop(start);
    return (0);
}