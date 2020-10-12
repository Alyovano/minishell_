/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:32:05 by user42            #+#    #+#             */
/*   Updated: 2020/10/12 15:53:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define OK 0
#define FAIL 1

/*
** Des librairies
*/

#include "../libft/libftprintfgnl.h"

/*
** Des structures
*/

/* (s_user)
** Dans cette struct je vais tenter de garder slm ce qui sera
** utile dans la premiere partie du projet -> Ce qui est relatif au parsing
** aux entrees de l'utilisateur et les infos du systeme
*/
typedef struct      s_user
{
    char **user_env;
    char *user_input;
}                   t_user;

/*
** Des fonctions
*/

int         parsing_input(char *input, t_user *start);
int		    check_quote(t_user *start);

/*
** Quote multilignes (Bonus ?)
*/

char        *verify_quote_integrity(char *input);

#endif