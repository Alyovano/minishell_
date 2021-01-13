/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:55:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_exit(t_env *env, t_list *lst, t_user *start)
{
	(void)env;
	(void)lst;
	(void)start;
	t_list *tmp;

	tmp = start->line;

	ft_printf("exit\n");
	//free_double_tab(env->tab); // CE TABLEAU EST MAUDIT
	free_double_tab(start->user_cmd_tab);
	while (lst)
	{
		free_double_tab(lst->tab_cmd);
		free(lst->content);
		lst = lst->next;
	}
	while (start->line)
	{
		free(start->line->content);
		start->line = start->line->next;
	}
	start->line = tmp;
	free(start->line);
	free(lst);
	//free(start->user_input);
	//free(env);
	exit(EXIT_SUCCESS);
}