#include "../includes/minishell.h"
//Ici il restera des failles dues a backslash avant la quote ...

// L'appel de verify_quote_integrity c'est le fameux bonus que je fais pour rire

/* commenter la fonction, elle gérère des faux positifs (ex. echo Hello\") not working
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
    while (start->user_input[i])
    {
        j = 0;
        if (start->user_input[i] == '\'')
        {
            backslash = 0;
            while (start->user_input[i + j] && start->user_input[i + j] == '\\')
            {
                j--;
                backslash++;
            }
            if (backslash % 2 == 0)
                quote_token++;
        }
        else if (start->user_input[i] == '"')
        {
            backslash = 0;
            while (start->user_input[i + j] && start->user_input[i + j] == '\\')
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
} */

// cas d'erreur minishell> "'"

int         parsing_input(char *input, t_user *start)
{
    int is_valid;

    is_valid = 0;
    start->user_input = ft_strdup(input);
    is_valid = parsing_quote(input);
    if (is_valid == 0)
        printf("OK : quotes\n");
    else
        printf("BAD : quotes\n");
    
}