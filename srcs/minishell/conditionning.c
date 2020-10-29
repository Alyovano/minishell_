/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2020/10/29 11:56:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function to get amount of char till specified character
** EX. get_len_till_char(0, ' ', "echo lol" -> return 4
*/

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

/*
** Function like strcmp but ignores '\'' and '"' for compare 
*/

/*
int         str_cmp_and_ignore(char *to_cmp, char *str)
{
	int i;
    int j;

	i = 0;
    j = 0;
	if ((!to_cmp || !str))
		return (0);
	while ((to_cmp[j] && str[i]) && (to_cmp[j] == str[i] || \
                            to_cmp[j] == '\'' || to_cmp[j] == '"'))
    {
        if (to_cmp[j] == '\'' || to_cmp[j] == '"')
            j++;
        else
        {
            i++;
            j++;
        }
    }
    if (to_cmp[j] == '\'' || to_cmp[j] == '"')
        return (0);
    else //else werror does not compile ;((((
        return ((int)(to_cmp[j] - str[i]));
}
*/

/*
** Last split to store data in t_list
** builtin, flags, argu
** "echo" is the only builtin to manage with flags
** for other elements, everything after builtin goes to argu
*/

void        last_split(t_list *lst)
{
    int i;
    //int j;
    char *tmp;

    tmp = ft_strdup(lst->content);
    i = get_len_till_char(0, ' ', tmp);
    //j = 0;
    lst->builtin = ft_substr(tmp, 0, i);
    // if (ft_strncmp(lst->builtin, "echo", 5) == 0)
    // {
    //     if (tmp[i + 1] == '-')
    //     {
    //         i++;
    //         j = i;
    //         while (tmp[i] && (tmp[i + 1] == 'e' || tmp[i + 1] == 'E' || tmp[i + 1] == 'n'))
    //             i++;
    //         if (tmp[i + 1] == ' ')
    //         {
    //             //Valid flag
    //             // Do not print flag, add to flag
    //             lst->flag = ft_substr(tmp, j, (i - j) + 1);
    //             lst->argu = ft_substr(tmp, i + 2, ft_strlen(tmp));
    //         }
    //         else
    //         {
    //             //flag unknown
    //             lst->argu = ft_substr(tmp, j, ft_strlen(tmp));
    //         }
    //     }
    //     else
    //     {
    //         //no flag, add end to argu
    //         lst->argu = ft_substr(tmp, i + 1, ft_strlen(tmp)); 
    //     }
    // }
    //else
    lst->flag = ft_strdup("empty");// temporaire pcq printf crash sinon
    lst->argu = ft_substr(tmp, i + 1, ft_strlen(tmp));
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
        lst = lst->next;
    }
}

/*
** Function to prepare for exectution
** last split to update t_list (builtin, flag, argu)
*/

int         conditionning(t_user *start)
{
    t_list *lst;
    void   *ptr;
    ptr = start->line;
    if (start->user_cmd_tab[0])
    {
        while (start->line)
        {
            lst = start->line->content;
            while (lst)
            {
                last_split(lst);
                lst = lst->next;
            }
            //debug(start->line->content);
            start->line = start->line->next;
        }
        start->line = ptr;
    }
    return (0);
}