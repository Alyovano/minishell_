/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_environnement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:55:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** size = check_arg_nb(arg) + 1; compte le nombre de coupe
** a appliquer a l'argument (combien de ligne va-t-on add au tableau env)
*/

// int     catch_env_var(char *arg, char *env_line)
// {
// 	int i = 0;
// 	if (arg[i] == env_line[i])
// 		return (0);
// 	return (-1);
// meme avec un truc aussi basique ca crash, il y a un probleme bien plus profond dans l'allocation
// }

int     catch_env_var(char *arg, char *env_line)
{
    unsigned int            i;
    char              **split;

    i = 0;
    split = ft_split(arg, '=');
    while (split[0][i] && env_line[i])
    {
		// printf("%d\n", i);
		// printf("%c\n", split[0][i]);
		printf("env line = %s\n", env_line);
		printf("str arg = %s\n", split[0]);
        if (split[0][i] != env_line[i])
            break ;
        i++;
    }
    if ((env_line[i] == '\0' || env_line[i] == '=') && i == ft_strlen(split[0])) // crash ici
    {
        free_double_tab(split);
        return (0);
    }
    free_double_tab(split);
    return (1);
}

// int     catch_env_var(char *arg, char *env_line)
// {
// 	unsigned int i;

// 	i = 0;
// 	if (!arg || !env_line)
// 		return (-1);
// 	while (arg[i] && env_line[i])
// 	{
// 		if (arg[i] != '=' && env_line[i] != '=')
// 		{
// 			if (arg[i] != env_line[i])
// 				return (-1);
// 		}
// 		else
// 		{
// 			if (env_line[i] == '=' && arg[i] == '=')
// 				return (0);
// 			else if ((env_line[i] == '=' && arg[i] == '\0') || (env_line[i] == '\0' && arg[i] == '='))
// 				return (0);
// 			else
// 				return (-1);
// 		}
// 		i++;
// 	}
// 	if (i == ft_strlen(arg) || i == ft_strlen(env_line))
// 		return (0);
// 	return (-1);
// }

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
            //free(tmp);
            return (ft_strdup(arg));
        }
        i++;
    }
    return (ft_strdup(tmp));
}
