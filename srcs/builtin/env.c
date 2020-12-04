#include "../includes/minishell.h"

/*
** env ne fait que print les var qui ont une valeur assignee
** il peut aussi en ajouter ex
**         $ env lol=56
** ensuite il print le tableau
** les valeurs ajoutees par l'apl de env sont detruite apres le print
*/

/*
** Check si la var possede une valeur
*/

char        **parsing_arg(char *arg);

int         have_value(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int         ft_env(t_env *env, char *arg)
{
    (void)env;
    (void)arg;
    char **arg_tab;
    int i;

    i = 0;
    arg_tab = parsing_arg(arg);
    // while (env->tab[i])
    // {
    //     if (have_value(env->tab[i]) == 1)
    //     {
    //         ft_printf("%s\n", env->tab[i]);
    //     }
    //     i++;
    // }
    while (arg_tab[i])
    {
        ft_printf("%s\n", arg_tab[i]);
        i++;
    }
    printf("COUCOU\n");
  	return (0);
}