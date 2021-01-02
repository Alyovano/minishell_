#include "../includes/minishell.h"

/*
** size = check_arg_nb(arg) + 1; compte le nombre de coupe
** a appliquer a l'argument (combien de ligne va-t-on add au tableau env)
*/

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

/*
** Pour savoir si une var existe dans le tableau env
** Si -1 alors la var n'existe pas
** si i > -1 alors i represente la position de la var dans le tableau
*/

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

/*
** Remplace la valeur d'une var d'environnement
** Cette fonction ne verifie pas son existence
*/

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
