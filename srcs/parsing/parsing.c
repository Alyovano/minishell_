#include "../includes/minishell.h"

char        **input_to_tab(t_user *start, t_quote *quote)
{
    int i = 0;
    int split_nb = 1;
    quote->token_in_simple_quote = 0;
    quote->token_in_dquote = 0;
    while (start->user_input[i])
    {
        if (start->user_input[i] == '\'' 
        && (get_backslash(start->user_input, i) == 0))
        { 
            // ma simple quote commence ici si je suis entre
            quote->token_in_simple_quote = 1;
            quote_get_len_and_validity(start, quote, i + 1);
            i += quote->len;
            quote->token_in_simple_quote = 0;
            ft_printf("Cette squote mesure [%d] et est valide si 0 -> [%d]\n"
                , quote->len, quote->verif);
        }
        if (start->user_input[i] == '"' 
        && (get_backslash(start->user_input, i) == 0))
        { 
            // ma double quote commence ici si je suis entre
            quote->token_in_dquote = 1;
            quote_get_len_and_validity(start, quote, i + 1);
            i += quote->len;
            quote->token_in_dquote = 0;
            ft_printf("Cette dquote mesure [%d] et est valide si 0 -> [%d]\n"
                , quote->len, quote->verif);
        }
        if (start->user_input[i] == ';')
            split_nb ++;
        i++;
    }
    printf("Nombre de partie a spliter == [%d]\n", split_nb);
}

int         parsing_input(char *input, t_user *start)
{
    t_quote *quote;

    if (!(quote = malloc(sizeof(quote))))
        return (-1);
    start->user_input = ft_strdup(input);
    input_to_tab(start, quote);
    // int is_valid;

    // is_valid = 0;
    // is_valid = parsing_quote(start, quote);
    // if (is_valid == 0)
    //     printf("OK : quotes\n");
    // else
    //     printf("BAD : quotes\n");
    
}