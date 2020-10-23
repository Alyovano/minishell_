/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:20:17 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 09:15:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int         maybe_split(char *str, int i)
{
    if (str[i] == '|')
    {
        if (get_backslash(str, i) == 0)
            return (0);
    }
    return (1);
}

static int quote_get_len_and_validity2(char *str, t_quote *quote, int i)
{
    init_quotes_to_fix(quote);
    while (str[i] 
    && (quote->token_in_simple_quote % 2 != 0 || quote->token_in_dquote % 2 != 0))
    {
        if (str[i] == '"')
        {
            if (get_backslash(str, i) == 0 && quote->token_in_simple_quote % 2 == 0)
                quote->token_in_dquote++;
        }
        else if (str[i] == '\'')
        {
            if (quote->token_in_simple_quote % 2 == 0 && quote->token_in_dquote % 2 == 0)
            {
                if (get_backslash(str, i) == 0)
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

static t_list         *cut_input_to_tab(t_quote *quote, char *str)
{
    int		k = 0;
    int		i = 0;
    int		j = 0;
	t_list	*cmd;
	t_list *test2;
	char *test;

    while (str[i])
    {
        init_quotes_to_fix(quote);
        if (str[i] == '\'' 
        && (get_backslash(str, i) == 0))
        {
            quote->token_in_simple_quote = 1;
            quote_get_len_and_validity2(str, quote, i + 1);
            i += quote->len;
            quote->token_in_simple_quote = 0;
        }
        if (str[i] == '"' 
        && (get_backslash(str, i) == 0))
        { 
            quote->token_in_dquote = 1;
            quote_get_len_and_validity2(str, quote, i + 1);
            i += quote->len;
            quote->token_in_dquote = 0;
        }
        if (maybe_split(str, i) == 0)
        {
			test = ft_str_n_dup(str + j, i - j);
			//ft_printf("Maybe split: %s\n", test);
            //printf("Je suis la\n");
			if (k == 0)
				cmd = ft_lstnew(test);
			else
			{
				ft_lstadd_back(&cmd, ft_lstnew(test));
			}
            k++;
            j = i + 2;
        }
        i++;
    }
    if (str[i] == 0 && quote->verif == 0)
    {
		test = ft_str_n_dup(str + j, i - j);
		//ft_printf("End: %s\n", test);
        if (k == 0)
			cmd = ft_lstnew(test);
		else
		{
			ft_lstadd_back(&cmd, ft_lstnew(test));
			//ft_printf("in: %s\n", cmd->content);
			(void)test2;
			/*
			test2 = cmd->next;
			ft_printf("in 2: %s\n", test2->content);
			*/
		}
        k++;
    }
    return (cmd);
}

void	print_lst(t_list *line)
{
	t_list *cmd;

	while (line->next != NULL)
	{
		cmd = line->content;
		while (cmd->next != NULL)
		{
			write(1, "1", 1);
			ft_printf("line: %s\n", cmd->content);
			cmd = cmd->next;
		}
		ft_printf("line: %s\n", cmd->content);
		line = line->next;
	}
	
}

void print2(void *str)
{
	ft_printf("cmd: %s\n", (char *)str);
}

void print(void *line)
{
	t_list *lst;
	lst = (t_list *)line;
	ft_printf("Line: \n");
	ft_lstiter(lst, &print2);
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
	
		/*
		else
		{
			tmp = ft_lstnew(start->user_cmd_tab[i]);
			if (i == 0)
				start->line = ft_lstnew(tmp);
			else
			{
				ft_lstadd_back(&start->line, ft_lstnew(tmp));
			}
		}
		*/
		
		i++;
	}
	
	tmp = start->line;
	/*
	if (tmp->next == NULL)
		print(tmp->content);
	while (tmp->next != NULL)
	{
		ft_printf("Line: \n");
		ft_lstiter(tmp, &print);
		tmp = tmp->next;
	}
	*/
	ft_lstiter(tmp, &print);
	//print(tmp->content);
	/*
	tmp = start->line->content;
	ft_printf("First elem: %s\n", tmp->content);
	*/



	
	/*
	tmp = start->line->content;
	if (start->line->next != NULL)
		ft_printf("1 elemn t_list: %s\n", tmp->content);
	print_lst(start->line);
	*/
	//ft_lstiter(start->line, &print);
}
