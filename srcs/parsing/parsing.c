#include "../includes/minishell.h"


int         is_my_quote(char *str, char quote_needed)
{
    char token;
    int i;

    token = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == quote_needed)
        {
            token = 1;
            break ;
        }
        i++;
    }
    if (token == 1)
        return (i);
    else
        return (0);
}

char        *quote_prompt(char *input, char quote_needed)
{
    char *next_str;
    char *tmp;

    while (1)
    {
        quote_needed == '\'' ? ft_printf("quote>") : ft_printf("dquote>");
        get_next_line(0, &next_str);
        if (is_my_quote(next_str, quote_needed) > 0)
        {
            tmp = ft_strjoin(input, next_str);
            return (tmp);
        }
        input = ft_strjoin(input, next_str);
        //free(next_str);
    }
}

char        *catch_more_quote(char *input, int token_quote)
{
    char quote_verif;

    quote_verif = 0;
    quote_verif = token_quote % 2 == 0 ? '"' : '\'';
    //Ici, j'admets que quote_verif a la valeur de la quote qu'on cherche
    quote_prompt(input, quote_verif);
}

char        *verify_line_integrity(char *input)
{
    int i;
    char *input_cleaned;
    char token_quote;
    char token_dquote;

    i = 0;
    token_dquote = 0;
    token_quote = 0;
    while (input && *input && input[i])
    {
        if (input[i] == '\'')
            token_quote++;
        if (input[i] == '"')
            token_dquote++;
        i++;
    }
    if (token_quote % 2 == 0 && token_dquote % 2 == 0)
        return (input);
    else
    {
        input_cleaned = catch_more_quote(input, token_quote);
        return (input_cleaned);
    }
}

//Ici il restera des failles dues a backslash avant la quote ...

int         parsing_input(char *input, t_user *start)
{
    start->user_Input = ft_strdup(input);
    start->user_Input = verify_line_integrity(start->user_Input);
    printf("%s\n", start->user_Input);
    return (0);
}