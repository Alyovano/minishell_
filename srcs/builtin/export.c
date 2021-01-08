/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:55:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// char        **arg_to_tab(char *arg, int size, t_token_env *token)
// {
//     int var_token;
//     char **tab;

//     var_token = 0;
//     tab = malloc(sizeof(char**) * (size));
//     // tab[size - 1] = NULL;
//     if (tab == NULL)
//         malloc_error();
//     while (arg[token->i])
//     {
//         while (arg[token->i] && arg[token->i] != ' ')
//         {
//             if ((arg[token->i] == '"' || arg[token->i] == '\'') && get_backslash(arg, token->i) == 0)
//                 token->i += quote_len(arg + token->i);
//             var_token = 1;
//             token->i++;
//         }
//         if (var_token == 1)
//         {
//             tab[token->k] = ft_str_n_dup(arg + token->j, token->i - token->j);
//             token->k++;
//             var_token = 0;
//             token->j = token->i;
//         }
//         token->i++;
//         // if (!tab[token->k] || tab[token->k][0] == '\0')
//         //     break ;
//     }
//     return (tab);
// }

// char        **add_arg_to_env(t_env *env, char **arg_tab, t_token_env *token)
// {
//     char **tmp;

//     tmp = malloc(sizeof(char**) * 
//         (((double_tab_size(env->tab) + double_tab_size(arg_tab)) + 1)));
//     if (tmp == NULL)
//         malloc_error();
//     while (env->tab[token->i])
//     {
//         tmp[token->i] = ft_strdup(env->tab[token->i]);
//         token->i++;
//     }
//     tmp[token->i] = NULL;
//     while (arg_tab[token->j])
//     {
//         if (arg_tab[token->j][0] != '\0') 
//         {
//             token->k = check_if_exist(env->tab, arg_tab[token->j]);
//             if (token->k != -1)
//             {
//                 tmp[token->k] = replace_var_value(tmp[token->k], arg_tab[token->j]);
//                 token->j++;
//             }
//             else
//             {
//                 tmp[token->i] = ft_strdup(arg_tab[token->j]);
//                 token->i++;
//                 token->j++;
//             }
//         }
//         else
//             token->j++;
//     }
//     tmp[token->i] = NULL;
//     free_copy(arg_tab, env);
//     return (tmp);
// }


// int         export_add_new_var(t_env *env, char *arg)
// {
//     t_token_env *token;
//     char        **arg_tab;
//     int         size;

//     token = malloc(sizeof(t_token_env));
//     if (!token)
//         malloc_error();
//     (void)env; // a delete
//     // go 
//     size = check_arg_nb(arg) + 1;
//     token_init(token);
//     arg_tab = arg_to_tab(arg, size, token);
//     for (int i = 0 ; arg_tab[i] ; i++)
//         printf("AVANT %s\n", arg_tab[i]);
//     token_init(token);
//     arg_tab = parsing_arg(arg_tab);
//     //env->tab = add_arg_to_env(env, arg_tab, token);
//     free(token);
//     return (ARGS);
// }

// int        handle_var_in_arg(char *arg)
// {
//     //char *tmp;
//     int i;
//     int jump_space;

//     i = 0;
//     jump_space = 0;
//     while (arg && arg[jump_space] == ' ')
//         jump_space++;
//     while (arg[jump_space + i] && arg[jump_space + i] != ' ')
//     {
//         if ((arg[jump_space + i] == '"' || arg[jump_space + i] == '\'') && get_backslash(arg, jump_space + i) == 0)
//                 i += quote_len(arg + (jump_space + i));
//         i++;
//     }
//     // tmp = ft_substr(arg, (unsigned int)jump_space, (unsigned int)i);
//     // printf("MATEMP = %s\n", tmp);
//     return (jump_space + i);
// }

// char         **new(t_env *env, t_list *lst)
// {
//     int var_position = 0;
// 	(void)lst;
//     int i = 0;
//     int j = 0;
//     int k = 0;
//     char *tmp;
//     char **new_tab;

//     //printf("Go pour expoter\n");
//     new_tab = malloc(sizeof(char**) * 
//         (((double_tab_size(env->tab) + check_arg_nb(arg) + 1))) + 1);
//     while (env->tab[i])
//     {
//         new_tab[i] = ft_strdup(env->tab[i]);
//         i++;
//     }
//     new_tab[i + 1] = NULL;
//     while (arg[j])
//     {
//         j += handle_var_in_arg(arg + k);
//         tmp = ft_str_n_dup(arg + k, j);
//         tmp = clear_arg(tmp);
//         //printf("Ma nouvelles temp = %s\n", tmp);
//         // jump

//         var_position = check_if_exist(new_tab, tmp);
//         if (var_position == -1)
//         {
//             new_tab[i] = ft_strdup(tmp);
//             free(tmp);
//             i++;
//             new_tab[i] = NULL;
//         }
//         else
//         {
//             // ici elle existe deja
//             // je crois que ca leak ici a cause de replace_var_value
//             new_tab[var_position] = replace_var_value(new_tab[var_position], tmp);
//         }
//         k = j + 1;
//         //j++;
//     }
//     new_tab[i] = NULL;
//     //free_double_tab(env->tab);
//     // for (int test = 0; new_tab[test] ; test++)
//     //     printf("Mon nouveau tableau :%s\n", new_tab[test]);
//     return (new_tab);
// }

int			export_new_var(t_env *env, t_list *lst)
{
	(void)env;
	(void)lst;

	for (int test = 0; lst->tab_cmd[test] ; test++)
        printf("Mon nouveau tableau :%s\n", lst->tab_cmd[test]);
	return (0);
}

int         ft_export(t_env *env, t_list *lst)
{
    env->swap_token = 0;
	printf("Premiere case == %s\n", lst->tab_cmd[0]);
    if (double_tab_size(lst->tab_cmd) == 1)
    {
        env->export = copy_double_tab(env->tab);
        sort_export(env);
        export_without_args(env);
        free_double_tab(env->export);
		 // status = 0 ici
        return (NO_ARGS);
    }
    else
    {
		printf("else\n");
		export_new_var(env, lst);
        for (int test = 0; env->tab[test] ; test++)
            printf("Mon nouveau tableau :%s\n", env->tab[test]);
		return (-1); // pour le moment
    }
    return (ARGS);
}