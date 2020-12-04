#include "../includes/minishell.h"

/*
** Je commence le debut du parsing sous l'appel de GNL
** On attend l'input, on l'envoie dans le parseur
*/

    // ici une boucle qui free toute la liste t_list ?
    // il ne faut surtout pas free le pointeur *start
    // car il n'est alloue que dans le main 

int     end_loop_free(t_user *start, char *str, int token_used)
{
    int i;

    i = 0;
    while (token_used == 1 && start->user_cmd_tab[i])
    {
        free(start->user_cmd_tab[i]);
        i++;
    }
    if (token_used == 1)
        free(start->user_cmd_tab);
    free(str);
    return (0);
}

void	ft_sig(int value)
{
    (void)value;

    write(1, "\n", 1);
	// ft_printf("\n");
    // ft_printf("minishell> ");
}

int     minishell_loop(t_user *start, t_env *env)
{
    int     used;
    char    *user_input;

	// signal(SIGINT, ft_sig);
	//signal(SIGQUIT, ft_sig);
    //signal(SIGINT, SIG_IGN);
    while (1)
    {
        used = 0;
        ft_printf("minishell> ");   
        get_next_line(0, &user_input);
        if (ft_strcmp(user_input, "") != 0)
        {
            used = 1;
            if (parsing_input(user_input, start, env) != -1)
            {
                if (conditionning(start) != -1)
                {
                    execution(start, env);
                }
            }
        }
        end_loop_free(start, user_input, used);
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