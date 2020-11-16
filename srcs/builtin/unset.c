#include "../includes/minishell.h"

// AU DESSUS LIBFT A DELETE LORS DE L'AJOUT AU MINISHELL

int     unset_built(t_env *env, char *arg)
{
    char **arg_tab;

    
}

int     main(int ac, char **av, char **environnement)
{
    t_env   *env;

    (void)ac;
    (void)av;
    if (!(env = malloc(sizeof(env))))
        return (-1);
    env->tab = copy_double_tab(environnement);
    uset_built();
    return (0);
}