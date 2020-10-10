#include "../includes/minishell.h"
#define NO_QUOTE -1

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
        return (NO_QUOTE);
}

/*
** Algo qui enregistre les input dans les sous shells quote>/dquote
** dans des variables tmp a tours de roles. Le sous shell (d)quote>
** prend fin quand la quote d'entree est denouveau entree par l'utilisateur
*/

char        *quote_prompt(char *input, char quote_needed)
{
    char *next_str;
    char *tmp;
    char *tmp_two;
    int where_is_my_quote;
    int token;

    token = 0;
    while (1)
    {
        quote_needed == '\'' ? ft_printf("quote> ") : ft_printf("dquote> ");
        get_next_line(0, &next_str);
        where_is_my_quote = is_my_quote(next_str, quote_needed);
        token++;
        if (token == 1)
        {
            tmp = ft_strjoin(input, next_str);
            free(input); 
            free(next_str);
            if (where_is_my_quote > NO_QUOTE)
                return (tmp);
        }
        else if (token % 2 == 0)
        {
            tmp_two = ft_strjoin(tmp, next_str);
            free(tmp);
            free(next_str);
            if (where_is_my_quote > NO_QUOTE)
                return (tmp_two);
        }
        else if (token % 2 == 1)
        {
            tmp = ft_strjoin(tmp_two, next_str);
            free(tmp_two);
            free(next_str);
            if (where_is_my_quote > NO_QUOTE)
                return (tmp);
        }
    }
}

char        *catch_more_quote(char *input, int token_quote)
{
    char quote_verif;
    char *tmp_verif;

    quote_verif = 0;
    quote_verif = token_quote % 2 == 0 ? '"' : '\'';
    tmp_verif = quote_prompt(input, quote_verif);
    return (tmp_verif);
}

char        *verify_quote_integrity(char *input)
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