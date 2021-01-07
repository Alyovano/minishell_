/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 15:41:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function to get amount of char till specified character
** EX. get_len_till_char(0, ' ', "echo lol" -> return 4
*/

int		get_len_till_char(int start, char c, char *str)
{
	t_quote quote;

	quote.squote = -1;
	quote.dquote = -1;
	while (str[start])
	{
		if (str[start] == '\'' && (get_backslash(str, start) == 0))
			quote.squote *= -1;
		if (str[start] == '"' && (get_backslash(str, start) == 0))
			quote.dquote *= -1;
		if (quote.dquote == -1 && quote.squote == -1)
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

void	set_fd_in_out(int id, int size, t_list *lst)
{
	if (id == 0)
	{
		lst->stdout_fd = 1;
		lst->stdin_fd = 0;
	}
	else if (id == size - 1)
	{
		lst->stdout_fd = 0;
		lst->stdin_fd = 1;
	}
	else
	{
		lst->stdout_fd = 1;
		lst->stdin_fd = 1;
	}
}
/*
int		print_tabbbbbssssss(t_user *start, t_quote *quote)
{
	int i;

	i = 0;
	if (init_double_tab_cmd(start) == -1)
		return (-1);
	cut_input_to_tab(start, quote);
	while (start->user_cmd_tab[i])
	{
		ft_printf("Conteeennnnt: %s\n", start->user_cmd_tab[i++]);
	}
	return (0);
}*/

/*
** Last split to store data in t_list
** builtin, flags, argu
** "echo" is the only builtin to manage with flags
** for other elements, everything after builtin goes to argu
*/

void	last_split(t_list *lst, int id, int size)
{
	int			i;
	int			j;
	char		*tmp;
	t_user		start;
	t_quote		quote;

	i = 0;
	start.user_input = ft_strdup(lst->content);
	start.split_nb = 1;
	while (start.user_input[i])
	{
		quote.squote = 0;
		quote.dquote = 0;
		i = input_to_tab_verif(&start, &quote, i);
		is_split_tokenize(&start, i);
		i++;
	}
	//ft_printf("nb to split: %d\n", start.split_nb);
	split_tokenize(&start, &quote);
	i = 0;/*
	while (start.user_cmd_tab[i])
	{
		ft_printf("user-cmd_tab: |%s|\n", start.user_cmd_tab[i]); //need to clear empty '\0' and space before elem
 		i++;
	}*/
	//print_tabbbbbssssss(&start, &quote); 
	tmp = ft_strdup(lst->content);
	j = 0;
	while (tmp[j] && tmp[j] == ' ')
		j++;
	i = get_len_till_char(j, ' ', tmp);
	lst->builtin = ft_substr(tmp, j, i);
	lst->flag = NULL;
	lst->argu = ft_substr(tmp, i + 1, ft_strlen(tmp));
	set_fd_in_out(id, size, lst);
	free(tmp);
}

/*
** Function to show every element of t_list
*/

void	debug(t_list *lst)
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

int		conditionning(t_user *start)
{
	t_list	*lst;
	void	*ptr;
	int		i;
	int		size;

	ptr = start->line;
	if (!start->user_cmd_tab)
		return (-1);
	while (start->line)
	{
		i = 0;
		lst = start->line->content;
		size = ft_lstsize(lst);
		while (lst)
		{
			if (remove_redirrect_alloc(lst) == -1)
				return (-1);
			last_split(lst, i, size);
			lst = lst->next;
			i++;
		}
		start->line = start->line->next;
	}
	start->line = ptr;
	return (0);
}
