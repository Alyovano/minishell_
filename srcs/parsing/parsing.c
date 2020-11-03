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

void        token_to_parse_init(t_user *start)
{
    start->split_nb = 1;
    start->chevron_nb = 0;
}

int         parsing_input(char *input, t_user *start, t_env *env)
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
    error = check_input_start(start);
    if (error < 0)
    {
        error_output_token(error, NULL);
        return (-1);
    }
    error = input_to_tab(start, quote);
    if (error < 0)
    {
        error_output_token(error, NULL);
        return (-1);
    }
    error = check_pipe(start->user_input, quote);
    if (error < 0)
    {
        error_output_token(error, NULL);
        return (-1);
    }
    first_split_dirty_line(start, quote);
    clean_line(start, quote);
    add_environnement_var(start, quote, env);
    split_pipe(start, quote);
    if (quote->verif == 0)
    {
        printf("Quote valides\n");
        return (1);
    }
    else
    {
        printf("Quote invalides\n");
        error_output_token(-5, NULL);
        return (-1);
    }
}