#include "../includes/minishell.h"

//Ici il restera des failles dues a backslash avant la quote ...

int         parsing_input(char *input, t_user *start)
{
    start->user_Input = ft_strdup(input);
    // ICI on va clear les '\', pour etre safe avec les quotes
    start->user_Input = verify_quote_integrity(start->user_Input);
    ft_printf("%s\n", start->user_Input);
    return (0);
}