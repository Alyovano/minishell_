/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:58:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 10:58:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_all(t_user *start)
{
	void	*tmp;
	t_list	*lst;

	tmp = start->line;
	while (start->line)
	{
		lst = start->line->content;
		while (lst)
		{
			free(lst->content);
			free_double_tab(lst->in_types);
			free_double_tab(lst->in);
			free_double_tab(lst->out_types);
			free_double_tab(lst->out);
			free_double_tab(lst->tab_cmd);
			lst = lst->next;
		}
		start->line = start->line->next;
	}
	start->line = tmp;
	free(start->line);
	free(lst);
}
