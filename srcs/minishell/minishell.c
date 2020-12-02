#include "../includes/minishell.h"

/*
** Je commence le debut du parsing sous l'appel de GNL
** On attend l'input, on l'envoie dans le parseur
*/

void	ft_sig(int value)
{
    (void)value;

	ft_printf("\nminishell> ");
}


int     minishell_loop(t_user *start, t_env *env)
{
    char *user_input;

	// signal(SIGINT, ft_sig);
	// signal(SIGQUIT, ft_sig);
    while (1)
    {
        ft_printf("minishell> ");
        get_next_line(0, &user_input);
        if (ft_strcmp(user_input, "") != 0)
        {
            if (parsing_input(user_input, start, env) != -1)
            {
                if (conditionning(start) != -1)
                {
                    execution(start, env);
                }
            }
        }
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

int     main(int argc, char **argv, char **environnement)
{
    t_user  *start;
    t_env   *env;

    (void) argc;
    (void) argv;
    if (!(start = malloc(sizeof(start))))
        malloc_error();
    if (!(env = malloc(sizeof(env))))
        malloc_error();
    env->tab = copy_double_tab(environnement);
    minishell_loop(start, env);
    return (0);
}