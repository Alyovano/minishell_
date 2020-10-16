#include "../includes/minishell.h"

int         init_double_tab_cmd(t_user *start)
{
    int i;

    i = 0;
    start->user_cmd_tab = malloc(sizeof(start->user_cmd_tab) * (start->split_nb + 1));
    if (!start->user_cmd_tab)
        return (-1);
    while(i < start->split_nb + 1)
    {
        start->user_cmd_tab[i] = 0;
        i++;
    }
    return (0);
}

int         maybe_split(t_user *start, int i)
{
    if (start->user_input[i] == ';')
    {
        if (get_backslash(start->user_input, i) == 0)
            return (0);
    }
    return (1);
}

int         cut_input_to_tab(t_user *start, t_quote *quote)
{
    int k = 0;
    int i = 0;
    int j = 0;

    while (start->user_input[i])
    {
        quote->token_in_simple_quote = 0;
        quote->token_in_dquote = 0;
        if (start->user_input[i] == '\'' 
        && (get_backslash(start->user_input, i) == 0))
        {
            quote->token_in_simple_quote = 1;
            quote_get_len_and_validity(start, quote, i + 1);
            i += quote->len;
            quote->token_in_simple_quote = 0;
        }
        if (start->user_input[i] == '"' 
        && (get_backslash(start->user_input, i) == 0))
        { 
            quote->token_in_dquote = 1;
            quote_get_len_and_validity(start, quote, i + 1);
            i += quote->len;
            quote->token_in_dquote = 0;
        }
        //arrive ici dans split, on sait qu'il peut pas y avoir d'erreur
        // ICI : Erreur algorythmique, jsp pourquoi, ca coupe pas a la bonne taille
        // ca crash, c'est mal culculer, c'est super pourri, je m'y remet demain
        if (maybe_split(start, i) == 0)
        {
            printf("Je suis la\n");
            start->user_cmd_tab[k] = ft_substr(start->user_input + j, 0, (i - j));
            k++;
            j += i;
        }
        i++;
    }
    if (start->user_input[i] == 0)
    {
        printf("fin de str\n");
        start->user_cmd_tab[k] = ft_substr(start->user_input + j - 1, 0, (i - j));
        k++;
    }
    return (0);
}

int         first_split_dirty_line(t_user *start, t_quote *quote)
{
    if (init_double_tab_cmd(start) == -1)
        return (-1);
    int i = 0;
    printf("Nb split = [%d]\n", start->split_nb);
    cut_input_to_tab(start, quote);
    while (start->user_cmd_tab[i])
    {
        printf("[%s]\n", start->user_cmd_tab[i]);
        i++;
    }
    return (0);
}