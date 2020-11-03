#include "../includes/minishell.h"

int         our_env(t_env *env)
{
    int i;

    i = 0;
    while(env->tab[i])
    {
        ft_printf("%s\n", env->tab[i]);
        i++;
    }
  	return (0);
}