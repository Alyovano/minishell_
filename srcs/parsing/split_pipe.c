/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:20:17 by user42            #+#    #+#             */
/*   Updated: 2021/01/04 13:57:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Same function as maybe_split, 
** but str[i] == ';' is replaced with '|'
*/

static int         maybe_split(char *str, int i)
{
    if (str[i] == '|')
    {
        if (get_backslash(str, i) == 0)
            return (0);
    }
    return (1);
}

/*
** Same function as quote_get_len_and_validity, 
** but t_user *start is replaced by char *str
*/

static int quote_get_len_and_validity2(char *str, t_quote *quote, int i)
{
    quote->len = 0;
    quote->verif = 0;
    while (str[i] 
    && (quote->t_in_squote % 2 != 0 || quote->t_in_dquote % 2 != 0))
    {
        if (str[i] == '"')
        {
            if (get_backslash(str, i) == 0 && quote->t_in_squote % 2 == 0)
                quote->t_in_dquote++;
        }
        else if (str[i] == '\'')
        {
            if (quote->t_in_squote % 2 == 0 && quote->t_in_dquote % 2 == 0)
            {
                if (get_backslash(str, i) == 0)
                    quote->t_in_squote++;
            }
            else if (quote->t_in_squote % 1 == 0 && quote->t_in_dquote % 2 == 0)
                quote->t_in_squote++;
        }
        i++;
        quote->len++;
    }
    quote->verif = (quote->t_in_dquote % 2) + (quote->t_in_squote % 2);
    return (quote->len - 1);
}

/*
** Same function as cut_input_to_tab, 
** but t_user *start is replaced by char *str
** a t_list cmd is created in place of char **tab for previus split
*/

static t_list         *cut_input_to_tab(t_quote *quote, char *str)
{
    int		k = 0;
    int		i = 0;
    int		j = 0;
	t_list	*cmd;
	char *temp;

    while (str[i])
    {
        init_quotes_to_fix(quote);
        if (str[i] == '\'' 
        && (get_backslash(str, i) == 0))
        {
            quote->t_in_squote = 1;
            quote_get_len_and_validity2(str, quote, i + 1);
            i += quote->len;
            quote->t_in_squote = 0;
        }
        if (str[i] == '"' 
        && (get_backslash(str, i) == 0))
        { 
            quote->t_in_dquote = 1;
            quote_get_len_and_validity2(str, quote, i + 1);
            i += quote->len;
            quote->t_in_dquote = 2;
        }
        if (maybe_split(str, i) == 0)
        {
			temp = ft_str_n_dup(str + j, i - j);
			if (k == 0)
				cmd = ft_lstnew(temp);
			else
				ft_lstadd_back(&cmd, ft_lstnew(temp));
            k++;
            j = i + 1;
            
            if (str[j + 1] == ' ')
                j++;
                
        }
        i++;
    }
    if (str[i] == 0 && quote->verif == 0)
    {
		temp = ft_str_n_dup(str + j, i - j);
        if (k == 0)
			cmd = ft_lstnew(temp);
		else
			ft_lstadd_back(&cmd, ft_lstnew(temp));
        k++;
    }
    return (cmd);
}

int		find_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
** Function to split start->user_cmd_tab[i] with '|'
** Split is stored to start->line (type t_list)
** In each t_list->content there is another t_list
** ex. minishell> echo hello | grep -e ; echo lol
** t_list lst1->content = echo hello
** t_list lst1->content = grep -e
** t_list lst2->content = echo lol
** t_lsit start_line-> content = lst1, lst2
*/

void	split_pipe(t_user *start, t_quote *quote)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (start->user_cmd_tab[i])
	{
		tmp = cut_input_to_tab(quote, start->user_cmd_tab[i]);
		if (i == 0)
			start->line = ft_lstnew(tmp);
		else
		{
			ft_lstadd_back(&start->line, ft_lstnew(tmp));
		}		
		i++;
	}
    // if (start->user_cmd_tab[0])
    //     print_list(start);
}
