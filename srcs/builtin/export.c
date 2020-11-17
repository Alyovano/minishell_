#include "../includes/minishell.h"
#define NO_ARGS 0
#define ARGS 1

/*
int		get_backslash(char *str, int i)
{
	int nb_backslash;

	nb_backslash = 0;
	while (str[--i] && str[i] == '\\')
		nb_backslash++;
	return (nb_backslash % 2);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	if (!dst || !src)
		return (0);
	i = ft_strlen(src);
	if (size > 0)
	{
		j = 0;
		while (src[j] != '\0' && j < size - 1)
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = '\0';
	}
	return (i);
}
char	*ft_strdup(const char *s1)
{
	size_t	longueur;
	char	*tab;

	longueur = ft_strlen(s1) + 1;
	if (!(tab = malloc(sizeof(char) * longueur)))
		return (NULL);
	ft_strlcpy(tab, s1, longueur);
	return (tab);
}
int     double_tab_size(char **src)
{
    int i;

    i = 0;
    while (src[i] != 0)
        i++;
    return (i);
}
char    **copy_double_tab(char **src)
{
    char **new_Tab;
    int size;
    int i;

    i = 0;
    size = double_tab_size(src);
    new_Tab = malloc(sizeof(char**) * (size + 1));
    if (!new_Tab)
        return (NULL);
    new_Tab[size] = 0;
    while (src[i])
    {
        new_Tab[i] = ft_strdup(src[i]);
        i++;
    }
    return (new_Tab);
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*stockdst;
	unsigned char	*stocksrc;
	size_t			count;

	stocksrc = (unsigned char*)src;
	stockdst = (unsigned char*)dst;
	count = 0;
	if (!dst && !src)
		return (NULL);
	while (count < n)
	{
		stockdst[count] = stocksrc[count];
		count++;
	}
	return (stockdst);
}
char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*finalstr;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!((finalstr = malloc(sizeof(char) * (size1 + size2 + 1)))))
		return (NULL);
	ft_memcpy(finalstr, s1, size1);
	ft_memcpy(finalstr + size1, s2, size2);
	finalstr[size1 + size2] = '\0';
	return (finalstr);
}
char	*ft_str_n_dup(const char *s1, int size)
{
	size_t	longueur;
	char	*tab;

	longueur = size + 1;
	if (!(tab = malloc(sizeof(char) * longueur)))
		return (NULL);
	ft_strlcpy(tab, s1, longueur);
	return (tab);
}
*/
// AU DESSUS LIBFT A DELETE LORS DE L'AJOUT AU MINISHELL
// AU DESSUS LIBFT A DELETE LORS DE L'AJOUT AU MINISHELL
// AU DESSUS LIBFT A DELETE LORS DE L'AJOUT AU MINISHELL

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
        printf("%s %s\n", "declare -x", env->export[i++]);
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
        if (env->export[i + 1])
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

//-------------------ARG TO TAB---------------------------

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

int         free_double_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (0);
}

/*
** Probleme ici -> Les frees ne tiennent pas en fin de fonction
*/ 

char        **add_arg_to_env(t_env *env, char **arg_tab)
{
    char **tmp;
    int size;
    int i;
    int j;

    i = 0;
    j = 0;
    size = (double_tab_size(env->tab) + double_tab_size(arg_tab));
    tmp = malloc(sizeof(char**) * (size + 1));
    while (env->tab[i])
    {
        tmp[i] = env->tab[i];
        i++;
    }
    while (arg_tab[j])
    {
        tmp[i] = arg_tab[j];
        i++;
        j++;
    }
    tmp[i - 1] = NULL;
    //free_double_tab(env->tab);
    //free_double_tab(arg_tab);
    //env->tab = copy_double_tab(tmp);
    return (tmp);
}

int         export_add_new_var(t_env *env, char *arg)
{
    char **arg_tab;

    arg_tab = parsing_arg(arg);
    
    env->tab = add_arg_to_env(env, arg_tab);
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
        while(env->tab[i]) {
            printf("ENV=[%s]\n",env->tab[i++]);
        }
    }
    return (ARGS);
}

// int     main(int argc, char **argv, char **environnement)
// {
//     t_env   *env;

//     (void) argc;
//     (void) argv;
//     if (!(env = malloc(sizeof(env))))
//         return (-1);
//     env->tab = copy_double_tab(environnement);
//     env->export = copy_double_tab(env->tab);
//     ft_export(env, "'prem'='56' lopl= tri um=565'lolo lol'");
//     return (0);
// }
