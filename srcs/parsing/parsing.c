#include "../includes/minishell.h"
#define OK 0
#define FAIL 1
//Ici il restera des failles dues a backslash avant la quote ...

// L'appel de verify_quote_integrity c'est le fameux bonus que je fais pour rire

int         check_quote_number(t_user *start)
{
    int i;
    int j;
    int quote_token;
    int dquote_token;
    int backslash;

    i = 0;
    quote_token = 0;
    dquote_token = 0;
    backslash = 0;
    while (start->user_Input[i])
    {
        j = 0;
        if (start->user_Input[i] == '\'')
        {
            backslash = 0;
            while (start->user_Input[i + j] && start->user_Input[i + j] == '\\')
            {
                j--;
                backslash++;
            }
            if (backslash % 2 == 0)
                quote_token++;
        }
        else if (start->user_Input[i] == '"')
        {
            backslash = 0;
            while (start->user_Input[i + j] && start->user_Input[i + j] == '\\')
            {
                j--;
                backslash++;
            }
            if (backslash % 2 == 0)
                dquote_token++;
        }
        i++;
    }
    if (quote_token % 2 == 0 && dquote_token % 2 == 0)
        return (OK);
    else
        return (FAIL);
}

// cas d'erreur minishell> "'"

int         parsing_input(char *input, t_user *start)
{
    start->user_Input = ft_strdup(input);
    if (check_quote_number(start) == FAIL)
        return (ft_printf("Bad quotes conditionning\n"));
    //backslash_gestion(start);
    //start->user_Input = verify_quote_integrity(start->user_Input);
    //ft_printf("%s\n", start->user_Input);
    return (0);
}