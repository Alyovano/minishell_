/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:55:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** env ne fait que print les var qui ont une valeur assignee
** il peut aussi en ajouter ex
**         $ env lol=56
** ensuite il print le tableau
** les valeurs ajoutees par l'apl de env sont detruite apres le print
*/

/*
** Check si la var possede une valeur
*/

// char        **parsing_arg_env(char *arg)
// {
//     char **arg_tab;
//     //int  size;
//     int  i;

//     i = 0;
//     //size = check_arg_nb(arg) + 1;
//     //arg_tab = arg_to_tab(arg, size); EN ATTENTE de export
//     while (arg_tab[i])
//     {
//         arg_tab[i] = first_clear_arg(arg_tab[i]);
//         i++;
//     }
//     return (arg_tab);
// }

// int         have_value(char *str)
// {
//     int i;

//     i = 0;
//     while (str && str[i])
//     {
//         if (str[i] == '=')
//             return (1);
//         i++;
//     }
//     return (0);
// }

int         ft_env(t_env *env, t_list *lst)
{
	(void)lst;
	int i;

	i = 0;
	while (env->tab[i])
	{
		ft_printf("%s\n", env->tab[i]);
		i++;
	}
	return (0);
    // char **arg_tab;
    // int i;

    // i = 0;
    // arg_tab = parsing_arg_env(arg);
    // while (env->tab[i])
    // {
    //     if (have_value(env->tab[i]) == 1)
    //     {
    //         ft_printf("%s\n", env->tab[i]);
    //     }
    //     i++;
    // }
    // i = 0;
    // while (arg_tab[i])
    // {
    //     if (have_value(arg_tab[i]))
    //         ft_printf("%s\n", arg_tab[i]);
    //     i++;
    // }
    // free_double_tab(arg_tab);
}