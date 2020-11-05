#include "../includes/minishell.h"
#define NO_ARG 0

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
    return (NO_ARG);
}

int         sort_export(t_env *env)
{
    int i;
    int j;
    char *tmp;
    int token;

    i = 0;
    j = 0;
    while (env->export[i])
    {
        token = 0;
        j = 0;
        if (env->export[i + 1])
        {
            while (env->export[i] && env->export[i + 1] 
            && env->export[i][j] == env->export[i + 1][j])
                j++;
            if (env->export[i][j] > env->export[i + 1][j])
            {
                tmp = ft_strdup(env->export[i]);
                free(env->export[i]);
                env->export[i] = ft_strdup(env->export[i + 1]);
                free(env->export[i + 1]);
                env->export[i + 1] = ft_strdup(tmp);
                free(tmp);
                token = -1;  
            }
        }
        i++;
        if (token == -1)
            i = 0;
    }
}

int         ft_export(t_env *env, char *arg)
{
    sort_export(env);
    if (!arg || *arg == '\0')
        return (export_without_args(env));
}

int     main(int argc, char **argv, char **environnement)
{
    t_env   *env;

    (void) argc;
    (void) argv;
    if (!(env = malloc(sizeof(env))))
        return (-1);
    env->tab = copy_double_tab(environnement);
    env->export = copy_double_tab(env->tab);
    ft_export(env, "");
    return (0);
}