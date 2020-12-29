#include "../includes/minishell.h"

/*
** Export recoit la structure avec le tableau d'environnement
** et l'argument qui suit l'appel de export
** Si pas d'argu : il print le tableau
** Si argu, il le parse, et ajoute le(s) vars si elles sont valides
** dans un cas invalide il retourne une erreur
**/

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
        malloc_error();
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

char        **add_arg_to_env(t_env *env, char **arg_tab, t_token_env *token)
{
    char **tmp;

    tmp = malloc(sizeof(char**) * 
        (((double_tab_size(env->tab) + double_tab_size(arg_tab)) + 1)));
    if (tmp == NULL)
        malloc_error();
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
        malloc_error();
    token_init(token);
    arg_tab = parsing_arg(arg);
    env->tab = add_arg_to_env(env, arg_tab, token);
    free(token);
    return (ARGS);
}

int         ft_export(t_env *env, char *arg)
{
    printf("ARG = %s\n", arg);
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
        export_add_new_var(env, arg);
    return (ARGS);
}