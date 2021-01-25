/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 16:06:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	lst->pid = -1;
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

int		conditionning2(t_user *start)
{
	int		i;
	t_list	*lst;
	int		size;

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
			if (ft_strcmp(lst->content, "") == 0)
				return (create_files(start));
			last_split(lst, i++, size);
			lst = lst->next;
		}
		start->line = start->line->next;
	}
	return (0);
}

/*
** Function to prepare for exectution
** last split to update t_list (builtin, flag, argu)
*/

int		conditionning(t_user *start)
{
	void	*ptr;

	ptr = start->line;
	if (!start->user_cmd_tab)
		return (-1);
	if (conditionning2(start) == -1)
		return (-1);
	start->line = ptr;
	return (0);
}
