/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:32:05 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 10:28:51 by user42           ###   ########.fr       */
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
**               Des structures
*/

/* 
** (s_user)
** Dans cette struct je vais tenter de garder slm ce qui sera
** utile dans la premiere partie du projet -> Ce qui est relatif au parsing
** aux entrees de l'utilisateur et les infos du systeme
*/
typedef struct      s_user
{
    char **user_env;
    char **user_cmd_tab;
    char *user_input;
    int  split_nb;
}                   t_user;

/*
** (s_quote)
** Rien de ouf juste quelques token pour verifier les validites
*/

typedef struct      s_quote
{
    int     token_in_dquote;
    int     token_in_simple_quote;
    int     verif;
    int     len;
}                   t_quote;

/*
**                 Des fonctions
*/

int         free_all(t_user *start, t_quote *quote);
int		    get_backslash(char *str, int i);
int         parsing_input(char *input, t_user *start);
int         quote_get_len_and_validity(t_user *start, t_quote *quote, int i);
int         first_split_dirty_line(t_user *start, t_quote *quote);
void        clean_line(t_user *start);

/*
** Quote multilignes (Bonus ?)
*/

char        *verify_quote_integrity(char *input);

#endif