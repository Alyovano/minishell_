#include "../includes/minishell.h"

int         export_without_args(t_env *env)
{
    int i;
    
    i = 0;
    while (env->export[i])
    {
        ft_printf("%s %s\n", "declare -x", env->export[i++]);
    }
    return (NO_ARGS);
}

int         sort_export_swap(t_env *env, int i)
{
    char *tmp;

    tmp = ft_strdup(env->export[i]);
    free(env->export[i]);
    env->export[i] = ft_strdup(env->export[i + 1]);
    free(env->export[i + 1]);
    env->export[i + 1] = ft_strdup(tmp);
    free(tmp);
    env->swap_token = -1;
    return (0);
}

int         sort_export(t_env *env)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (env->export[i])
    {
        env->swap_token = 0;
        j = 0;
        if (env->export[i + 1] && ft_strcmp(env->export[i], env->export[i + 1]) != 0)
        {
            while (env->export[i] && env->export[i + 1] 
            && env->export[i][j] == env->export[i + 1][j])
                j++;
            if (env->export[i][j] > env->export[i + 1][j])
                sort_export_swap(env, i);
        }
        i++;
        if (env->swap_token == -1)
            i = 0;
    }
    return (1);
}