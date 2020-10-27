#include "../includes/minishell.h"

int         conditionning(t_user *start)
{
    if (start->user_cmd_tab[0])
        print_list(start);
    return (0);
}