#include "../includes/minishell.h"

typedef struct      s_dollar
{
    char    *var_name;
    char    *var_content;
	char	*before_str;
	char	*after_str;
	char	*first_join;
	char	*second_join;
	int     start_cut;
    int     len;
	int		index;
}                   t_dollar;

char	*ft_strn_dup(const char *s1, int len)
{
	size_t	longueur;
	char	*tab;

	longueur = len;
	if (!(tab = malloc(sizeof(char) * longueur)))
		return (NULL);
	ft_strlcpy(tab, s1, longueur);
	return (tab);
}


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
    && (get_backslash(start->user_cmd_tab[i], j) == 0) && quote->dollar_quote % 2 == 0)
    {
        quote->token_in_simple_quote = 1;
        simple_quote_get_len_and_validity(start, quote, i, j + 1);
        j += quote->len;
        quote->token_in_simple_quote = 0;
    }
	if (start->user_cmd_tab[i][j] == '"'
    && (get_backslash(start->user_cmd_tab[i], j) == 0))
	{
		// ce token permet de savoir si on est pas deja dans une doucle quote
		// pcq si c'est le cas meme entre simple quote, il faudrait afficher
		// la var d'envi --- exemple de piege possible
		// input> " '$USER' "
		// output> "'alyovano'"
		quote->dollar_quote += 1;
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
        new = ft_substr(start->user_env[i], ft_strlen(var_name) + 1, ft_strlen(start->user_env[i]));
    else
        new = ft_strdup("");
    return (new);
}

//ici start->user_cmd_tab[i][j] == '$' au depart
int        dollar_var_name(t_user *start, int i, int j, t_dollar *dol)
{
	int tmp;
	int k;
	char *one;
	char *two;

    j += 1;
	tmp = j;
	k = 0;
    while (start->user_cmd_tab[i][j + k] && start->user_cmd_tab[i][j + k] != ' ' 
    && start->user_cmd_tab[i][j + k] != '\'' && start->user_cmd_tab[i][j + k] != '"' 
    && start->user_cmd_tab[i][j + k] != '=' && start->user_cmd_tab[i][j + k] != '.')
	{
		//j++;
		// k represente la len du nom de la variable d'envi
        k++; //Je suis pas sur dans la while pour : start->user_cmd_tab[i][j] != '='
	}
	printf("tmp apres%d\n", tmp);
	printf("Index apres %d\n", j);
	dol->var_name = ft_substr(start->user_cmd_tab[i], tmp, k);
    dol->var_content = check_var_in_env(start, dol->var_name);
	dol->before_str = ft_substr(start->user_cmd_tab[i], 0, j - 1);
	dol->after_str = ft_substr(start->user_cmd_tab[i], j + k, ft_strlen(start->user_cmd_tab[i]));
	one = ft_strjoin(dol->before_str, dol->var_content);
	two = ft_strjoin(one, dol->after_str);
	printf("%s\n", one);
	printf("%s\n", two);
	start->user_cmd_tab[i] = two;
	//dol->first_join = ft_strjoin(dol->before_str, dol->var_content);
	//dol->index = ft_strlen(dol->first_join);
	//dol->second_join = ft_strjoin(dol->first_join, dol->after_str);
	// printf("VARNAME[%s]\n", dol->var_name);
    // printf("VARCONTENT[%s]\n", dol->var_content);
	// printf("BEFORE CONTENT[%s]\n", dol->before_str);
	// printf("AFTER CONTENT[%s]\n", dol->after_str);
	// printf("FIRST JOIN[%s]\n", dol->first_join);
	//printf("SECOND JOIN[%s]\n", dol->second_join);
	//printf("SECOND JOIN LEN[%d]\n", dol->index);
	tmp = ft_strlen(one);
    return (tmp);
}

int         check_dollar_or_not_dollar(t_user *start, t_quote *quote, int i, t_dollar *dol)
{
    int j;

    j = 0;
	quote->dollar_quote = 0;
    while (start->user_cmd_tab[i][j])
    {
        j = check_simple_quote(start, quote, j, i);// jump sur la char apres la squote
        if (start->user_cmd_tab[i][j] == '$' && 
                    (get_backslash(start->user_cmd_tab[i], j) == 0))
        {
            j = dollar_var_name(start, i, j, dol);
        }
        j++;
    }
    return (0);
}

int         add_environnement_var(t_user *start, t_quote *quote)
{
    int i;

	t_dollar *dol;
    if (!(dol = malloc(sizeof(dol))))
	{
        return (-1);
	}
	i = 0;
	dol->start_cut = 0;
    while  (start->user_cmd_tab[i])
    {
        check_dollar_or_not_dollar(start, quote, i, dol);
        i++;
    }
    return (0);
}