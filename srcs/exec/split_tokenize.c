#include "../includes/minishell.h"

int			tokenize_space_index(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

/*
** Return 1 if space in begin and need to realloc
*/

char		**tokenize_realloc(char **tab)
{
	int		size;
	int		i;
	int		j;
	char	**ret;

	size = 0;
	i = -1;
	j = 0;
	while (tab[++i])
	{
		if (is_space_empty(tab[i]) == 0)
			size++;
	}
	ret = malloc(sizeof(char *) * (size + 1));
	if (!ret)
		malloc_error();
	i = -1;
	while (tab[++i])
	{
		if (is_space_empty(tab[i]) == 0)
		{
			size = tokenize_space_index(tab[i]);
			if (size == 0) //no space in front
				ret[j] = ft_strdup(tab[i]);
			else
				ret[j] = ft_substr(tab[i], size, ft_strlen(tab[i]));
			j++;
		}
	}
	ret[j] = NULL;
	return (ret);
}

/*
** Return 1: if str == '\0' or str contains only spaces
** Return 0: in other cases
*/

int			is_space_empty(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

/*
** Function to count number of splitable spaces to maloc tab after
*/

void		is_split_tokenize(t_user *start, int i)
{
	if (start->user_input[i] == ' ')
	{
		if (get_backslash(start->user_input, i) == 0)
			start->split_nb++;
	}
}

/*
** COPY FROM SPLIT DIRTY LINE but maybe split == " "
*/

int			maybe_split_tokenize(t_user *start, int i)
{
	if (start->user_input[i] == ' ')
	{
		if (get_backslash(start->user_input, i) == 0)
			return (0);
	}
	return (1);
}

int				cut_input_to_tab_tokenize(t_user *start, t_quote *quote)
{
	int k;
	int i;
	int j;

	k = 0;
	i = 0;
	j = 0;
	while (start->user_input[i])
	{
		init_quotes_to_fix(quote);
		if (start->user_input[i] == '\''
		&& (get_backslash(start->user_input, i) == 0))
		{
			quote->squote = 1;
			quote_get_len_and_validity(start, quote, i + 1);
			i += quote->len;
			quote->squote = 0;
		}
		if (start->user_input[i] == '"'
		&& (get_backslash(start->user_input, i) == 0))
		{
			quote->dquote = 1;
			quote_get_len_and_validity(start, quote, i + 1);
			i += quote->len;
			quote->dquote = 0;
		}
		if (maybe_split_tokenize(start, i) == 0)
		{
			start->user_cmd_tab[k] = ft_str_n_dup(start->user_input + j, i - j);
			k++;
			j = i;
		}
		i++;
	}
	if (start->user_input[i] == 0 && quote->verif == 0)
	{
		start->user_cmd_tab[k] = ft_str_n_dup(start->user_input + j, i - j);
		k++;
	}
	return (0);
}

char				split_tokenize(t_user *start, t_quote *quote)
{
	if (init_double_tab_cmd(start) == -1)
		return (-1);
	cut_input_to_tab_tokenize(start, quote);
	return (0);
}
