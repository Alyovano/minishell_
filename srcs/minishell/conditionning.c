/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 10:09:00 by user42           ###   ########.fr       */
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
** Function to split lst->content in multiple tokens in lst->tab_cmd
** tab_cms[0] = builtin
*/

void	last_split(t_list *lst, int id, int size)
{
	int			i;
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
	split_tokenize(&start, &quote);
	lst->tab_cmd = tokenize_realloc(start.user_cmd_tab);
	set_fd_in_out(id, size, lst);
	free(start.user_input);
	free_double_tab(start.user_cmd_tab);
}

void	init_lst(t_list *lst)
{
	lst->in_types = NULL;
	lst->out_types = NULL;
	lst->in = NULL;
	lst->out = NULL;
	lst->tab_cmd = NULL;
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
			init_lst(lst);
			if (remove_redirrect_alloc(lst) == -1)
				return (-1);
			last_split(lst, i++, size);
			lst = lst->next;
		}
		start->line = start->line->next;
	}
	start->line = ptr;
	return (0);
}
