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
    {
        perror("Malloc Failure\n");
        exit(EXIT_FAILURE);
    }
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

int     catch_env_var(char *arg, char *env_line)
{
    unsigned int            i;
    char              **split;

    i = 0;
    split = ft_split(arg, '=');
    while (split[0][i] && env_line[i])
    {
        if (split[0][i] != env_line[i])
            break ;
        i++;
    }
    if ((env_line[i] == '\0' || env_line[i] == '=') && i == ft_strlen(split[0]))
    {
        free_double_tab(split);
        return (0);
    }
    free_double_tab(split);
    return (1);
}

int         check_if_exist(char **tab, char *arg)
{
    int i;

    i = 0;
    while (tab[i])
    {
        if (catch_env_var(arg, tab[i]) == 0)
            return (i);
        i++;
    }
    return (-1);
}

char         *replace_var_value(char *tmp, char* arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
        {
            free(tmp);
            return (ft_strdup(arg));
        }
        i++;
    }
    return (ft_strdup(tmp));
}

char        **add_arg_to_env(t_env *env, char **arg_tab, t_token_env *token)
{
    char **tmp;

    tmp = malloc(sizeof(char**) * 
        (((double_tab_size(env->tab) + double_tab_size(arg_tab)) + 1)));
    if (tmp == NULL)
    {
        perror("Malloc Failure\n");
        exit(EXIT_FAILURE);
    }
    while (env->tab[token->i])
    {
        tmp[token->i] = ft_strdup(env->tab[token->i]);
        token->i++;
    }
    tmp[token->i] = NULL;
    while (arg_tab[token->j])
    {
        if (arg_tab[token->j][0] != '\0') 
        {
            token->k = check_if_exist(env->tab, arg_tab[token->j]);
            if (token->k != -1)
            {
                tmp[token->k] = replace_var_value(tmp[token->k], arg_tab[token->j]);
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
    char        **arg_tab;

    token = malloc(sizeof(t_token_env));
    if (!token)
    {
        perror("Malloc Failure\n");
        exit(EXIT_FAILURE);
    }
    token_init(token);
    arg_tab = parsing_arg(arg);
    // ici probablement parse encore pr comparer les argu entre eux et virer les doublons
    env->tab = add_arg_to_env(env, arg_tab, token);
    free(token);
    return (ARGS);
}

/*
** export <nom_de_var_pas_encore_dans_le_tableau> x2 ou x3 provoque une var repetee
*/

int         ft_export(t_env *env, char *arg)
{
    env->swap_token = 0;
    if (!arg || *arg == '\0')
    {
        env->export = copy_double_tab(env->tab);
        sort_export(env);
        export_without_args(env);
        free_double_tab(env->export);
        return (NO_ARGS);
    }
    else
    {
        export_add_new_var(env, arg);
    }
    return (ARGS);
}