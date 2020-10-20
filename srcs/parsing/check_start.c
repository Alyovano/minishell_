#include "../includes/minishell.h"

int         check_input_start(t_user *start)
{
    int i;

    i = 0;
    while (start->user_input[i] && start->user_input[i] == ' ')
        i++;
    if (start->user_input[i] == ';')
        return (-1);
    if (start->user_input[i] == '>')
    {
        if (start->user_input[i + 1])
        {
            i++;
            while (start->user_input[i] && start->user_input[i] == ' ')
                i++;
            if (start->user_input[i] == ';')
                return (-1);
            if (!start->user_input[i])
                return (-4);
            if (start->user_input[i] != ' ')
                return (0);
        }
        return (-4);
    }
    return (0);
}