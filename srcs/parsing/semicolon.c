#include "../includes/minishell.h"

int         check_semicolon_validity(t_user *start, int i)
{
    while (start->user_input[i] && start->user_input[i] == ' ')
    {
        i++;
    }
    if (start->user_input[i] == ';')
    {
        // erreur critique, bash arrete tout dans ce cas
        // il faudra evidemment sortir proprement ici
        return (-1);
    }
    return (0);
}

/*
** Si split_nb == -1 ca veut dire qu'on arrete tout pour cette ligne de cmd
*/

int         is_this_splitable(t_user *start, t_quote *quote, int i)
{
    (void)quote;
    if (start->user_input[i] == ';')
    {
        if (get_backslash(start->user_input, i) == 0)
        {
            if (check_semicolon_validity(start, i + 1) == -1)
            {
                start->split_nb = -1;
                return (-1);
            }
            else
            {
                start->split_nb++;
                return (0);
            }
        }
    }
    return (1);
}