#include "../includes/minishell.h"

int         check_semicolon_validity(t_user *start, int i)
{
    while (start->user_input[i] && start->user_input[i] == ' ')
    {
        i++;
    }
    if (start->user_input[i] == ';')
    {
        // erreur critique, bash arrete tout dans ce cas
        // il faudra evidemment sortir proprement ici
        return (-1);
    }
    return (0);
}

/*
** Si split_nb == -1 ca veut dire qu'on arrete tout pour cette ligne de cmd
*/

int         is_this_splitable(t_user *start, t_quote *quote, int i)
{
    (void)quote;
    if (start->user_input[i] == ';')
    {
        if (get_backslash(start->user_input, i) == 0)
        {
            if (check_semicolon_validity(start, i + 1) == -1)
            {
                //cas critique de double ;;
                start->split_nb = -1;
                return (-1);
            }
            else
            {
                start->split_nb++;
                return (0);
            }
        }
    }
    return (1);
}

int         input_to_tab_verif(t_user *start, t_quote *quote, int i)
{
    if (start->user_input[i] == '\'' 
    && (get_backslash(start->user_input, i) == 0))
        { 
        // ma simple quote commence ici si je suis entre
        quote->token_in_simple_quote = 1;
        quote_get_len_and_validity(start, quote, i + 1);
        i += quote->len;
        quote->token_in_simple_quote = 0;
    }
    if (start->user_input[i] == '"' 
    && (get_backslash(start->user_input, i) == 0))
    { 
        // ma double quote commence ici si je suis entre
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
        // On pourrait check les "<> >> $" ici aussi
        i++;
    }
    return (0);
}

/*
** Ne pas oublier de :
** Cas a patch -> minishell> ; echo lol
** Ce cas la doit retourner une erreur
*/

int         parsing_input(char *input, t_user *start)
{
    t_quote *quote;

    if (!input || !*input)
        return (0);
    if (!(quote = malloc(sizeof(quote))))
        return (-1);
    if (!(start->user_input = ft_strdup(input)))
        return (-1);
    start->split_nb = 1;
    if ((input_to_tab(start, quote) == -1))
    {
        //free_all(start, quote);
        ft_printf("bash: erreur de syntaxe près du symbole inattendu « ; »\n");
        return (-1);
    }
    first_split_dirty_line(start, quote);
    // Le chantier du debugger
    //-----------------------
    if (quote->verif == 0)
        printf("Quote valides\n");
    else
        printf("Quote invalides\n");
    return (1); //ligne temporaire pour faire taire le return non void
}