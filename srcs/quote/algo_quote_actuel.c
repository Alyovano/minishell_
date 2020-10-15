#include "../includes/minishell.h"

int parsing_quote(char *input)
{
    int i;
    int verif;
    t_quote quote;
 
    i = 0;
    verif = 0;
    quote.token_in_simple_quote = 0;
    quote.token_in_dquote = 0;
    while (input[i])
    {
        if (input[i] == '"')
        {
            if (get_backslash(input, i) == 0 && quote.token_in_simple_quote % 2 == 0)
                quote.token_in_dquote++;
        }
        else if (input[i] == '\'')
        {
            if (quote.token_in_simple_quote % 2 == 0 && quote.token_in_dquote % 2 == 0)
            {
                // premiere simple_quote
                if (get_backslash(input, i) == 0)
                    quote.token_in_simple_quote++;
            }
            else if (quote.token_in_simple_quote % 1 == 0 && quote.token_in_dquote % 2 == 0)
            {
                quote.token_in_simple_quote++;
            }
            // encore quelques doutes ici pt ? 
        }
        i++;
    }
    verif = (quote.token_in_dquote % 2) + (quote.token_in_simple_quote % 2);
    return (verif);
}