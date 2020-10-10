#ifndef MINISHELL_H
# define MINISHELL_H

#endif

/*
** Des librairies
*/

#include "../libft/alyovano.h"

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
    char **user_Env;
    char *user_Input;
}                   t_user;

/*
** Des fonctions
*/

int         parsing_input(char *input, t_user *start);

/*
** Quote multilignes (Bonus ?)
*/

char        *verify_quote_integrity(char *input);