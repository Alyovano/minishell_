/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2020/10/29 10:41:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         get_len_till_char(int start, char c, char *str)
{
    int i;

    i = 0;
    while (str[start])
    {
        start++;
        i++;
        if (str[i] == c)
            return (i);
    }
    if (str[i] == '\0')
        return (i);
    return (0);
}

void        last_split(t_list *lst)
{
    int i;
    int j;
    char *tmp;

    tmp = ft_strdup(lst->content);
    i = get_len_till_char(0, ' ', tmp);
    j = 0;
    lst->builtin = ft_substr(tmp, 0, i);
    if (ft_strncmp(lst->builtin, "echo", 5) == 0)
    {
        if (tmp[i + 1] == '-')
        {
            i++;
            j = i;
            while (tmp[i] && (tmp[i + 1] == 'e' || tmp[i + 1] == 'E' || tmp[i + 1] == 'n'))
            {
                i++;
            }
            if (tmp[i + 1] == ' ')
            {
                //Valid flag
                // Do not print flag, add to flag
                lst->flag = ft_substr(tmp, j, (i - j) + 1);
                lst->argu = ft_substr(tmp, i + 2, ft_strlen(tmp));
            }
            else
            {
                //flag unknown
                lst->argu = ft_substr(tmp, j, ft_strlen(tmp));
            }
        }
        else
        {
            //no flag, add end to argu
            lst->argu = ft_substr(tmp, i + 1, ft_strlen(tmp)); 
        }
        
    }
    else
    {
       lst->argu = ft_substr(tmp, i + 1, ft_strlen(tmp));
    }
    
    free(tmp);

}

void        next_line(t_list *lst)
{
    
    while (lst)
    {
        last_split(lst);
        lst = lst->next;
    }
    
}

void        debug(t_list *lst)
{
    ft_printf("\n\nDebug line: \n-----------------------------\n\n");
    while (lst)
    {
        ft_printf("Content: |%s|\n", (char *)lst->content);
        ft_printf("Builtin: |%s|\n", (char *)lst->builtin);
        ft_printf("Flag: |%s|\n", (char *)lst->flag);
        ft_printf("Argu: |%s|\n\n", (char *)lst->argu);
        lst = lst->next;
    }
}

int         conditionning(t_user *start)
{
    if (start->user_cmd_tab[0])
    {
        while (start->line)
        {
            next_line(start->line->content);
            debug(start->line->content);
            start->line = start->line->next;
        }
    }
    return (0);
}