#include "../includes/minishell.h"

/*
** Export recoit la structure avec le tableau d'environnement
** et l'argument qui suit l'appel de export
** Si pas d'argu : il print le tableau
** Si argu, il le parse, et ajoute le(s) vars si elles sont valides
** dans un cas invalide il retourne une erreur
**/

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

int         quote_len(char *str)
{
    int i;
    char quote;

    i = 1;
    quote = *str;
    while (str[i])
    {
        if (str[i] == quote && get_backslash(str, i) == 0)
        {
            break ;
        }
        i++;
    }
    return (i);
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

/*
** Prend l'argument, la nombre de de coupe (size) et
** le tableau fournit par la fonction precedente, renvoie
** le tableau remplit par chaque morceau de l'argument
*/

char        **arg_to_tab(char *arg, int size)
{
    int i;
    int j;
    int k;
    int token;
    char **tab;

    i = 0;
    j = 0;
    k = 0;
    token = 0;
    tab = malloc(sizeof(char**) * (size));
    tab[size - 1] = NULL;
    if (tab == NULL)
        exit(EXIT_FAILURE);
    while (arg[i])
    {
        while (arg[i] && arg[i] != ' ')
        {
            if ((arg[i] == '"' || arg[i] == '\'') && get_backslash(arg, i) == 0)
            {
                i += quote_len(arg + i);
            }
            token = 1;
            i++;
        }
        if (token == 1)
        {
            tab[k] = ft_str_n_dup(arg + j, i - j);
            k++;
            token = 0;
            j = i;
        }
        i++;
    }
    return (tab);
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
    return (tmp);
}

/*
** size = check_arg_nb(arg) + 1; compte le nombre de coupe
** a appliquer a l'argument (combien de ligne va-t-on add au tableau env)
*/

char        *first_clear_arg(char *str)
{
    char *tmp;

    tmp = clear_arg(str);
    free(str);
    str = ft_strdup(tmp);
    free(tmp);
    return (str);
}

char        **parsing_arg(char *arg)
{
    char **arg_tab;
    int  size;
    int  i;

    i = 0;
    size = check_arg_nb(arg) + 1;
    arg_tab = arg_to_tab(arg, size);
    while (arg_tab[i])
    {
        arg_tab[i] = first_clear_arg(arg_tab[i]);
        if (arg_tab[i][ft_strlen(arg_tab[i]) - 1] == '=' 
        && arg_tab[i][ft_strlen(arg_tab[i])] == '\0')
        {
            char *tmp;
            tmp = ft_strjoin(arg_tab[i], "\"\"");
            free(arg_tab[i]);
            arg_tab[i] = ft_strdup(tmp);
            free(tmp);
        }
        i++;
    }
    return (arg_tab);
}

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

int     catch_env_var(char *arg, char *env_line)
{
    unsigned int i;

    i = 0;
    while (arg[i] && env_line[i])
    {
        if (arg[i] != env_line[i])
            break ;
        i++;
    }
    if ((env_line[i] == '\0' || env_line[i] == '=') && i == ft_strlen(arg))
        return (0);
    return (1);
}

int         check_if_exist(t_env *env, char *arg)
{
    int i;

    i = 0;
    while (env->tab[i])
    {
        if (catch_env_var(arg, env->tab[i]) == 0)
            return (i);
        i++;
    }
    return (-1);
}

char        **add_arg_to_env(t_env *env, char **arg_tab, t_token_env *token)
{
    char **tmp;

    tmp = malloc(sizeof(char**) * 
        (((double_tab_size(env->tab) + double_tab_size(arg_tab)) + 1)));
    while (env->tab[token->i])
    {
        tmp[token->i] = ft_strdup(env->tab[token->i]);
        token->i++;
    }
    while (arg_tab[token->j])
    {
        if (arg_tab[token->j][0] != '\0') 
        {
            token->k = check_if_exist(env, arg_tab[token->j]);
            if (token->k != -1)
            {
                free(tmp[token->k]);
                tmp[token->k] = ft_strdup(arg_tab[token->j]);
                token->j++;
            }
            else
            {
                tmp[token->i] = ft_strdup(arg_tab[token->j]);
                token->i++;
                token->j++;
            }
        }
        else
            token->j++;
    }
    tmp[token->i] = NULL;
    free_copy(arg_tab, env);
    return (tmp);
}

void        token_init(t_token_env *token)
{
    token->i = 0;
    token->j = 0;
    token->k = 0;
}

int         export_add_new_var(t_env *env, char *arg)
{
    t_token_env *token;
    char **arg_tab;

    token = malloc(sizeof(t_token_env));
    if (!token)
    {
        perror("Malloc Failure\n");
        exit(0);
    }
    token_init(token);
    arg_tab = parsing_arg(arg);
    env->tab = add_arg_to_env(env, arg_tab, token);
    free(token);
    return (ARGS);
}

/*
** Reste encore une utilite de la cmd a faire, qui est d'update une valeur
** si la $VAR existe deja
*/

int         ft_export(t_env *env, char *arg)
{
    int i;

    i = 0;
    env->swap_token = 0;
    if (!arg || *arg == '\0')
    {
        env->export = copy_double_tab(env->tab);
        sort_export(env);
        export_without_args(env);
        while (env->export[i])
            free(env->export[i++]);
        free(env->export);
        return (NO_ARGS);
    }
    else
    {
        export_add_new_var(env, arg);
    }
    return (ARGS);
}