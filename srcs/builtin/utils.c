#include "../includes/minishell.h"

int         free_copy(char **arg_tab, t_env *env)
{
    int i;

    i = 0;
    while (arg_tab[i])
    {
        free(arg_tab[i]);
        i++;
    }
    i = 0;
    while (env->tab[i])
    {
        free(env->tab[i]);
        i++;
    }
    if (arg_tab)
        free(arg_tab);
    if (env->tab)
        free(env->tab);
    return (0);
}

int         check_arg_nb(char *arg)
{
    int i;
    int nb;
    int token;

    i = 0;
    nb = 0;
    token = 0;
    while (arg[i])
    {
        token = 0;
        while (arg[i] && arg[i] != ' ')
        {
            if ((arg[i] == '"' || arg[i] == '\'') && get_backslash(arg, i) == 0)
                i += quote_len(arg + i);
            token = 1;
            i++;
        }
        if (token == 1)
            nb += 1;
        i++;
    }
    return (nb);
}

char        *clear_arg(char *str)
{
    char *tmp;
    int i;
    int j;

    i = 0;
    j = 0;
    tmp = malloc(sizeof(char*) * (ft_strlen(str) + 1));
    if (str[i] == ' ')
        i += 1;
    while (str[i])
    {
        tmp[j] = str[i];
        if (str[i] == '\'' && get_backslash(str, i) == 0)
            tmp[j] = '"';
        i++;
        j++;
    }
    tmp[j] = 0;
    free(str);
    return (tmp);
}

/*
** Si un arg a un = mais pas de valeur ensuite
*/

char        **parsing_arg(char **arg_tab)
{
    char *tmp;
    int  i;

    i = 0;
    // for (int j ; arg_tab[j] ; j++)
    //     printf("APRES = %s\n", arg_tab[j]);
    while (arg_tab[i])
    {
        arg_tab[i] = first_clear_arg(arg_tab[i]);
        //printf("APRES  = %s\n", arg_tab[i]);
        // ici
        if (arg_tab[i][ft_strlen(arg_tab[i]) - 1] == '=' 
        && arg_tab[i][ft_strlen(arg_tab[i])] == '\0')
        {
            tmp = ft_strjoin(arg_tab[i], "\"\"");
            free(arg_tab[i]);
            arg_tab[i] = ft_strdup(tmp);
            free(tmp);
        }
        i++;
    }
    return (arg_tab);
}

char        *first_clear_arg(char *str)
{
    char *tmp;

    tmp = clear_arg(str);
    free(str);
    str = ft_strdup(tmp);
    free(tmp);
    return (str);
}