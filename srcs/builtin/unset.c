#include "../includes/minishell.h"
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
int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t len_s2;
	size_t len_s1;
	size_t len;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1) + 1;
	len_s2 = ft_strlen(s2) + 1;
	len = len_s1;
	if (len_s1 > len_s2)
		len = len_s2;
	if (len > n)
		return (ft_memcmp(s1, s2, n));
	return (ft_memcmp(s1, s2, len));
}
int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char*)s1;
	ss2 = (unsigned char*)s2;
	i = 0;
	if (n == 0 || (!ss1 || !ss2))
		return (0);
	while ((ss1 || ss2) && ss1[i] == ss2[i] && i < (n - 1))
		i++;
	return ((int)(ss1[i] - ss2[i]));
}

// AU DESSUS LIBFT A DELETE LORS DE L'AJOUT AU MINISHELL


/*
** s1 = Mon argu a chercher dans le tableau
** s2 = la ligne du tableau 
**
** return 0 -> La var existe dans le tableau
** return 1 -> Cette var n'est pas dans le tableau
*/
int     catch_env_var(char *arg, char *env_line)
{
    int i;

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

int     unset_built(t_env *env, char *arg)
{
    int i = 0;
    int size = double_tab_size(env->tab);
    int token = 0;
    //printf("ARG LEN=[%ld]\n", ft_strlen(arg));
    printf("%s\n", env->tab[29]);
    printf("%s\n", arg);
    token = catch_env_var(arg, env->tab[29]);
    printf("%d\n", token);
    //printf("SIZE= [%d]\n", size);



    // while (env->tab[i])
    // {
    //     token = 0;
    //     token = ft_strncmp(env->tab[i], arg, ft_strlen(arg));
    //     printf("%d\n", token);
    //     printf("%s\n", env->tab[i++]);
    // }
}

// int     main(int ac, char **av, char **environnement)
// {
//     t_env   *env;

//     (void)ac;
//     (void)av;
//     if (!(env = malloc(sizeof(env))))
//         return (-1);
//     env->tab = copy_double_tab(environnement);
//     unset_built(env, "VTE_VERSION");
//     return (0);
// }