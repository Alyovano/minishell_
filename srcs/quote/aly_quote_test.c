#include "../includes/minishell.h"

typedef struct      s_quote
{
    int     token_in_dquote;
    int     token_in_simple_quote;
}                   t_quote;

int		get_backslash(char *str, int i)
{
	int nb_backslash;

	nb_backslash = 0;
	while (str[--i] && str[i] == '\\')
		nb_backslash++;
	return (nb_backslash % 2);
}

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
    if (verif != 0)
        printf("Invalide\n");
    else
        printf("OK\n");
    return 0;
}

int main()
{
    char *user_input;
    while (1)
    {
        ft_printf("minishell> ");
        get_next_line(0, &user_input);
        parsing_quote(user_input);
        free(user_input); // Faudra tout free, pas que input
    }
}