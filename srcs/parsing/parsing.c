#include "../includes/minishell.h"

int         input_to_tab_verif(t_user *start, t_quote *quote, int i)
{
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
    return (i);
}

int         input_to_tab(t_user *start, t_quote *quote)
{
    int i = 0;

    while (start->user_input[i])
    {
        quote->token_in_simple_quote = 0;
        quote->token_in_dquote = 0;
        i = input_to_tab_verif(start, quote, i);
        if (is_this_splitable(start, quote, i) == -1)
            return (-1);
        if (is_this_redirectable(start, quote, i) == -1)
            return (-2);
        if (is_this_redirectable_reverse(start, quote, i) == -1)
            return (-3);
        i++;
    }
    return (0);
}

void        error_output_token(t_user *start, int error)
{
    (void)start;
    if (error == -1)
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « ; »\n");
    else if (error == -2)
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « > »\n");
    else if (error == -3)
        ft_printf("Minishell cannot do that: No multilines : « < »\n");
    //Ici ca va free comme jaja

}

void        token_to_parse_init(t_user *start)
{
    start->split_nb = 1;
    start->chevron_nb = 0;
}

int         parsing_input(char *input, t_user *start)
{
    int error;
    t_quote *quote;

    if (!input || !*input)
        return (0);
    if (!(quote = malloc(sizeof(quote))))
        return (-1);
    if (!(start->user_input = ft_strdup(input)))
        return (-1);
    token_to_parse_init(start);
    error = input_to_tab(start, quote);
    if (error < 0)
    {
        error_output_token(start, error);
        return (-1);
    }
    first_split_dirty_line(start, quote);
    clean_line(start);
    //-----------------------
    //-----------------------
    //-----------------------
    // Le chantier du debugger
    //-----------------------
    //-----------------------
    //-----------------------
    int i = 0;
    printf("Nb split = [%d]\n", start->split_nb);
    while (start->user_cmd_tab[i])
    {
        printf("[%s]\n", start->user_cmd_tab[i]);
        i++;
    }
    if (quote->verif == 0)
        printf("Quote valides\n");
    else
        printf("Quote invalides\n");
    return (1); //ligne temporaire pour faire taire le return non void
}