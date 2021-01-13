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

int     end_and_free(t_user *start)
{
    int i;

    i = 0;
    while (start->user_cmd_tab[i])
    {
        free(start->user_cmd_tab[i]);
        i++;
    }
    free(start->user_cmd_tab);
    return (0);
}

int     minishell_loop(t_user *start, t_env *env, char *argv)
{
    int     used;
    int     ret;
    char    *user_input;
	t_list	lst;

    (void)used;
    catch_signal();
    if (argv != NULL)
    {
        used = 0;
        user_input = ft_strdup(argv);
        if (ft_strcmp(user_input, "") != 0)
        {
            used = 1;
            if (parsing_input(user_input, start, env) != -1)
            {
                if (conditionning(start) != -1)
                {
					lst.tab_cmd = malloc(sizeof(char *) * 2);
					if (!lst.tab_cmd)
						malloc_error();
					lst.tab_cmd[1] = NULL;
					lst.tab_cmd[0] = ft_strdup("MINISHELL_TEST_DONT_CHECK_ERROR_MESSAGE=yes");
                    //ft_export(env, &lst); bug avec export
                    execution(start, env);
                }
            }
        }
		// Un free pour le testeur aussi ? 
    }
    else
    {
        while (1)
        {
            used = 0;
            //prompt();
			g_reg = 0;
			ft_printf("Minishell> ");
            ret = get_next_line(0, &user_input);
            verif_ret(ret, user_input);
            if (ft_strcmp(user_input, "") != 0)
            {
                used = 1;
                if (parsing_input(user_input, start, env) != -1)
                {
                    if (conditionning(start) != -1)
                    {
                        execution(start, env);
                    }
					
                   //free_all(start);
                }
            }
            free(user_input);
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