#include "../includes/minishell.h"

int         parsing_input(char *input, t_user *start)
{
    start->user_Input = ft_strdup(input);
    printf("%s\n", start->user_Input);
    return (0);
}