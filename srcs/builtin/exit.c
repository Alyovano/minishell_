/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/22 10:54:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	free_double_tab(env->tab); CE TABLEAU EST MAUDIT
**	free_double_tab(start->user_cmd_tab);
**
**	while (lst)
**	{
**		free_double_tab(lst->tab_cmd);
**		free(lst->content);
**		lst = lst->next;
**	}
**	while (start->line)
**	{
**		free(start->line->content);
**		start->line = start->line->next;
**	}
**	start->line = tmp;
**	free(start->line);
**	free(lst);
**	free(start->user_input);
**	free(env);
*/

int			ft_exit(t_env *env, t_list *lst, t_user *start)
{
	(void)env;
	(void)lst;
	ft_printf("exit\n");
	free_all(start);
	free(start);
	free_double_tab(env->tab);
	free(env);
	exit(EXIT_SUCCESS);
}
