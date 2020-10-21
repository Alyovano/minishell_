#include "../includes/minishell.h"

int simple_quote_get_len_and_validity(t_user *start, t_quote *quote, int i, int j)
{
    quote->len = 0;
    while (start->user_cmd_tab[i][j]
    && (quote->token_in_simple_quote % 2 != 0 || quote->token_in_dquote % 2 != 0))
    {
        if (start->user_cmd_tab[i][j] == '"')
        {
            if (get_backslash(start->user_cmd_tab[i], j) == 0 && quote->token_in_simple_quote % 2 == 0)
                quote->token_in_dquote++;
        }
        else if (start->user_cmd_tab[i][j] == '\'')
        {
            if (quote->token_in_simple_quote % 2 == 0 && quote->token_in_dquote % 2 == 0)
            {
                if (get_backslash(start->user_cmd_tab[i], j) == 0)
                    quote->token_in_simple_quote++;
            }
            else if (quote->token_in_simple_quote % 1 == 0 && quote->token_in_dquote % 2 == 0)
                quote->token_in_simple_quote++;
        }
        j++;
        quote->len++;
    }
    return (quote->len - 1);
}

int         check_simple_quote(t_user *start, t_quote *quote, int j, int i)
{
    if (start->user_cmd_tab[i][j] == '\'' 
    && (get_backslash(start->user_cmd_tab[i], j) == 0))
    {
        quote->token_in_simple_quote = 1;
        simple_quote_get_len_and_validity(start, quote, i, j + 1);
        j += quote->len;
        quote->token_in_simple_quote = 0;
    }
    return (j);
}
//=================================================================

int         str_check(char *str_envi, char *to_catch)
{
    int i;
    int len;
    int check;

    i = 0;
    check = 0;
    len = ft_strlen(to_catch);
    while (i < len)
    {
        if (to_catch[i] == str_envi[i])
        {
            check++;
        }
        i++;
    }
    if (check == len && str_envi[i] == '=')
        return (0);
    return (1);
}

char        *check_var_in_env(t_user *start, char *var_name)
{
    int i;
    int token_copy;
    char *new;

    i = 0;
    token_copy = 0;
    while (start->user_env[i])
    {
        if (str_check(start->user_env[i], var_name) == 0)
        {
            if (start->user_env[i])
            token_copy = 1;
            break ;
        }
        i++;
    }
    if (token_copy == 1)
        new = ft_substr(start->user_env[i], ft_strlen(var_name), ft_strlen(start->user_env[i]));
    else
        new = ft_strdup("");
    return (new);
}

char        *dollar_var_name(t_user *start, int i, int j)
{
    //ici start->user_cmd_tab[i][j] == '$' au depart
    int start_cut;
    char *var_name;
    char *var_content;
    // char *tmp;
    // char *tmp_two;
    // char *tmp_final;

    j += 1;
    start_cut = j;
    while (start->user_cmd_tab[i][j] && start->user_cmd_tab[i][j] != ' ' 
    && start->user_cmd_tab[i][j] != '\'' && start->user_cmd_tab[i][j] != '"' 
    && start->user_cmd_tab[i][j] != '=' && start->user_cmd_tab[i][j] != '.')
        j++; //Je suis pas sur dans la while pour : start->user_cmd_tab[i][j] != '='
    var_name = ft_substr(start->user_cmd_tab[i], start_cut, j);
    var_content = check_var_in_env(start, var_name);
    printf("VARNAME[%s]\n", var_name);
    printf("VARCONTENT[%s]\n", var_content);
    // tmp = ft_substr(start->user_cmd_tab[i], 0, j - (int)ft_strlen(var_name) - 1);
    // start_cut = ft_strlen(tmp);
    // tmp_two = ft_strjoin(tmp, var_content + 1);
    // free(tmp);
    // tmp = ft_substr(start->user_cmd_tab[i], start_cut, (int)ft_strlen(start->user_cmd_tab[i]));
    // tmp_final = ft_strjoin(tmp_two, tmp);
    // free(var_name);
    // free(var_content);
    // free(tmp);
    // free(tmp_two);
    // free(start->user_cmd_tab[i]);
    return (0);
}

int         check_dollar_or_not_dollar(t_user *start, t_quote *quote, int i)
{
    int j;

    j = 0;
    while (start->user_cmd_tab[i][j])
    {
        j = check_simple_quote(start, quote, j, i);// jump sur la char apres la squote
        if (start->user_cmd_tab[i][j] == '$' && 
                    (get_backslash(start->user_cmd_tab[i], j) == 0))
        {
            start->user_cmd_tab[i] = dollar_var_name(start, i, j);
            break ;
        }
        j++;
    }
    return (0);
}

int         add_environnement_var(t_user *start, t_quote *quote)
{
    int i;

    i = 0;
    while  (start->user_cmd_tab[i])
    {
        check_dollar_or_not_dollar(start, quote, i);
        i++;
    }
    return (0);
}