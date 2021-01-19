/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 09:24:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 10:09:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		print2(void *str)
{
	ft_printf("[%s]\n", (char *)str);
}

void		print(void *line)
{
	t_list *lst;

	lst = (t_list *)line;
	ft_printf("Line: \n");
	ft_lstiter(lst, &print2);
}

/*
** Fonction pour afficher la liste chainée contenue dans t_user
*/

void		print_list(t_user *start)
{
	ft_lstiter(start->line, &print);
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
		ft_printf("Stdin ? : |%d|\n\n", lst->stdin_fd);
		ft_printf("Stdout ?: |%d|\n\n", lst->stdout_fd);
		lst = lst->next;
	}
}
