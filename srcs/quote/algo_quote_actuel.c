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