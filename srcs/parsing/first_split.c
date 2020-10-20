#include "../includes/minishell.h"

char	*ft_str_n_dup(const char *s1, int size)
{
	size_t	longueur;
	char	*tab;

	longueur = size + 1;
	if (!(tab = malloc(sizeof(char) * longueur)))
		return (NULL);
	ft_strlcpy(tab, s1, longueur);
	return (tab);
}

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
    else 
        return (1);
    return (0);
}


// FIX 
// Il faudra tout reverifier encore une fois, ligne par ligne
// directement a l'interieur du tableau, des erreurs peuvent encore passer
// + norme |!|
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
        if (maybe_split(start, i) == 0)
        {
            printf("Je suis la\n");
            start->user_cmd_tab[k] = ft_str_n_dup(start->user_input + j, i - j);
            k++;
            j = i;
        }
        i++;
    }
    if (start->user_input[i] == 0 && quote->verif == 0)
    {
        printf("fin de str\n");
        start->user_cmd_tab[k] = ft_str_n_dup(start->user_input + j, i - j);
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