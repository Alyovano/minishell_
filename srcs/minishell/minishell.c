#include "../includes/minishell.h"

/*
** Je commence le debut du parsing sous l'appel de GNL
** On attend l'input, on l'envoie dans le parseur
*/

// ici une boucle qui free toute la liste t_list ?
// il ne faut surtout pas free le pointeur *start
// car il n'est alloue que dans le main 
// 2 
// Cette fonction nous fait actuellement crash

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

int     minishell_loop(t_user *start, t_env *env, char *argv)
{
    int     used;
    int     ret;
    char    *user_input;

    (void)used;
    catch_signal();
    if (argv != NULL)
    {
        //TESTEUR bash -c
        used = 0;
        user_input = ft_strdup(argv);
        if (ft_strcmp(user_input, "") != 0)
        {
            used = 1;
            if (parsing_input(user_input, start, env) != -1)
            {
                if (conditionning(start) != -1)
                {
                    ft_export(env, "MINISHELL_TEST_DONT_CHECK_ERROR_MESSAGE=yes");
                    execution(start, env);
                }
            }
        }
    }
    else
    {
        while (1)
        {
            used = 0;
            prompt();
            ret = get_next_line(0, &user_input);
            verif_ret(ret, user_input);
            //printf("ret = %d\n", ret);
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
            //g_reg = 1;
            //end_loop_free(start, user_input, used);
        }
    }
    
    
    return (0);
}

int     main(int argc, char **argv, char **environnement)
{
    t_user  *start;
    t_env   *env;

    if (!(start = malloc(sizeof(start))))
        malloc_error();
    if (!(env = malloc(sizeof(env))))
        malloc_error();
    env->tab = copy_double_tab(environnement);
    if (argc == 3 && ft_strcmp(argv[1], "-c") == 0)
        minishell_loop(start, env, argv[2]);
    else
        minishell_loop(start, env, NULL);
    // ICI un mega free ?
    return (0);
}