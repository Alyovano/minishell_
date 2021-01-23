/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:58:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 16:20:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_paths(char **paths)
{
	if (paths)
		free_double_tab(paths);
}

void		mega_free(t_list *lst)
{
	if (lst->content)
		free(lst->content);
	if (lst->in_types)
		free_double_tab(lst->in_types);
	if (lst->in)
		free_double_tab(lst->in);
	if (lst->out_types)
		free_double_tab(lst->out_types);
	if (lst->out)
		free_double_tab(lst->out);
	if (lst->tab_cmd)
		free_double_tab(lst->tab_cmd);
}

void		free_all(t_user *start)
{
	t_list	*lst;

	while (start->line && start->to_free >= 2)
	{
		lst = start->line->content;
		while (lst)
		{
			mega_free(lst);
			free(lst);
			lst = lst->next;
		}
		free(start->line);
		start->line = start->line->next;
	}
	if (start->to_free >= 1)
		free(start->user_input);
}
