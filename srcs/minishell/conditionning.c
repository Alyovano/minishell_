/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2020/12/11 09:22:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function to get amount of char till specified character
** EX. get_len_till_char(0, ' ', "echo lol" -> return 4
*/

int         get_len_till_char(int start, char c, char *str, t_quote *quote)
{
    quote->token_in_simple_quote = -1;
	quote->token_in_dquote = -1;
    while (str[start])
    {
        if (str[start] == '\'' && (get_backslash(str, start) == 0))
			quote->token_in_simple_quote *= -1;
		if (str[start] == '"' && (get_backslash(str, start) == 0))
			quote->token_in_dquote *= -1;
		if (quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1)
        {
            if (str[start] == c)
                return (start);
        }
        start++;
    }
    if (str[start] == '\0')
        return (start);
    return (0);
}

/*
** Last split to store data in t_list
** builtin, flags, argu
** "echo" is the only builtin to manage with flags
** for other elements, everything after builtin goes to argu
*/

void        last_split(t_list *lst, int id, int size)
{
    int         i;
    int         j;
    t_quote     *quote;
    char        *tmp;

    quote = malloc(sizeof(t_quote));
    if (!quote)
        exit(-1);
    tmp = ft_strdup(lst->content);
    j = 0;
    while (tmp[j] && tmp[j] == ' ')
        j++;
    i = get_len_till_char(j, ' ', tmp, quote);
    lst->builtin = ft_substr(tmp, j, i);
    lst->flag = NULL;
    lst->argu = ft_substr(tmp, i + 1, ft_strlen(tmp));
    if (id == 0)
    {
        //first elem, only stdout
        lst->stdout_fd = 1;
        lst->stdin_fd = 0;
    }
    else if (id == size - 1)
    {
        //last elem, only stdin
        lst->stdout_fd = 0;
        lst->stdin_fd = 1;
    }
    else
    {
        //mid elem, stdin, stdout
        lst->stdout_fd = 1;
        lst->stdin_fd = 1;
    }
    free(tmp);
}

/*
** Function to show every element of t_list
*/

void        debug(t_list *lst)
{
    ft_printf("\n\nDebug line: \n-----------------------------\n\n");
    while (lst)
    {
        ft_printf("Content: |%s|\n", (char *)lst->content);
        ft_printf("Builtin: |%s|\n", (char *)lst->builtin);
        ft_printf("Flag: |%s|\n", (char *)lst->flag);
        ft_printf("Argu: |%s|\n\n", (char *)lst->argu);
        ft_printf("Stdin ? : |%d|\n\n", lst->stdin_fd);
        ft_printf("Stdout ?: |%d|\n\n", lst->stdout_fd);
        lst = lst->next;
    }
}

/*
** Function to prepare for exectution
** last split to update t_list (builtin, flag, argu)
*/

int         conditionning(t_user *start)
{
    t_list  *lst;
    void    *ptr;
    int     i;
    int     size;
    t_quote quote;

    ptr = start->line;
    if (!start->user_cmd_tab)
        return (-1);
    if (start->user_cmd_tab[0])
    {
        while (start->line)
        {
            i = 0;
            lst = start->line->content;
            size = ft_lstsize(lst);
            while (lst)
            {
                init_redirrect(lst);
                //Je bosse ici actuellement sur les redirrections
                /*
                if (is_redirrect(lst, &quote) == 1)
                    ft_printf("Redirrection present in line\n");
                    */
                //ft_printf("content from lst: |%s|\n", lst->content);
                if (get_redirrect(lst, &quote) == -1)
                    return (-1);
                //print_double_tab(lst);
                last_split(lst, i, size);
                lst = lst->next;
                i++;
            }
            start->line = start->line->next;
        }
        start->line = ptr;
    }
    return (0);
}