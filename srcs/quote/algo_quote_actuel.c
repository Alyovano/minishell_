#include "../includes/minishell.h"

/*
** Retourne la taille de la quote
** stock dans quote->verif si elle est valide
** Si quote->len vaut -1 :
** - Alors la quote a ete slm ouverte et est invalide
** Si la quote->len vaut 1:
** Alors c'est une quote vide type "" ou ''
** Si quote->len > 1 :
** Je considere qu'il y a du texte recuperable dans la quote
*/

void    init_quote_len_validity(t_quote *quote)
{
    quote->len = 0;
    quote->verif = 0;
}

int quote_get_len_and_validity(t_user *start, t_quote *quote, int i)
{
    init_quote_len_validity(quote);
    while (start->user_input[i] 
    && (quote->token_in_simple_quote % 2 != 0 || quote->token_in_dquote % 2 != 0))
    {
        if (start->user_input[i] == '"')
        {
            if (get_backslash(start->user_input, i) == 0 && quote->token_in_simple_quote % 2 == 0)
                quote->token_in_dquote++;
        }
        else if (start->user_input[i] == '\'')
        {
            if (quote->token_in_simple_quote % 2 == 0 && quote->token_in_dquote % 2 == 0)
            {
                if (get_backslash(start->user_input, i) == 0)
                    quote->token_in_simple_quote++;
            }
            else if (quote->token_in_simple_quote % 1 == 0 && quote->token_in_dquote % 2 == 0)
                quote->token_in_simple_quote++;
        }
        i++;
        quote->len++;
    }
    quote->verif = (quote->token_in_dquote % 2) + (quote->token_in_simple_quote % 2);
    return (quote->len - 1);
}

int         quote_len(char *str)
{
    int i;
    char quote;

    i = 1;
    quote = *str;
    while (str[i])
    {
        if (str[i] == quote && get_backslash(str, i) == 0)
        {
            break ;
        }
        i++;
    }
    return (i);
}

char        *delete_quote(char *str)
{
    unsigned int i;
    unsigned int j;
    char *tmp;

    i = 0;
    j = 0;
    tmp = malloc(sizeof(char*) * (ft_strlen(str) + 1));
    if (tmp == NULL)
        exit(EXIT_FAILURE);
    while (str[i])
    {
        while (str[i] == '"' || str[i] == '\'')
            i++;
        tmp[j] = str[i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    free(str);
    return (tmp);
}