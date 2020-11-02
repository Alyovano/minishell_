/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:32:05 by user42            #+#    #+#             */
/*   Updated: 2020/11/02 08:57:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <sys/stat.h>

#define OK 0
#define FAIL 1

/*
** Des librairies
*/

#include "../libft/libftprintfgnl.h"
#include <wait.h>

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
    char    **user_env;
    char    **user_cmd_tab;
    char    *user_input;
    int     split_nb; //Token de validite + malloc size
    int     chevron_nb; //Token de validite inutilise
    t_list  *line;
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
    int     dollar_quote;
}                   t_quote;

/*
**                 Des fonctions
*/

int         free_all(t_user *start, t_quote *quote);
int         parsing_input(char *input, t_user *start);
int         quote_get_len_and_validity(t_user *start, t_quote *quote, int i);
int         check_input_start(t_user *start);
void        error_output_token(int error, char *str);
void        init_quotes_to_fix(t_quote *quote);
int	    	find_char(char *str, char c);

/*
**          Split
*/
char	    *ft_str_n_dup(const char *s1, int size);
void	    clean_spaces(t_user *start, t_quote *quote);
void        clean_line(t_user *start, t_quote *quote);
int         first_split_dirty_line(t_user *start, t_quote *quote);


/*
**          Pipe '|'
*/
int		    check_pipe(char *str, t_quote *quote);
void	    split_pipe(t_user *start, t_quote *quote);

/*
**          Semicolon; Chevron<>  Backslash\\
*/

int		    get_backslash(char *str, int i);
int         is_this_splitable(t_user *start, t_quote *quote, int i);
int         is_this_redirectable(t_user *start, t_quote *quote, int i);
int         is_this_redirectable_reverse(t_user *start, t_quote *quote, int i);

/*
**          Environnement - Variable - $
*/

int         add_environnement_var(t_user *start, t_quote *quote);

/*
** Quote multilignes (Bonus ?)
*/

char        *verify_quote_integrity(char *input);

/*
**    Preparation a l'execution
*/

int         conditionning(t_user *start);
int		    execution(t_user *start);
int		    dispatch_cmd(t_list *lst);
void	    clean_builtin(t_list *lst);
void		parse_flags(t_list *lst);
void    	clean_quote(char **str);
void		exec_pipe();

/*
** Debug (delete before last push)
*/

void	    print_list(t_user *start);
void        debug(t_list *lst);

#endif