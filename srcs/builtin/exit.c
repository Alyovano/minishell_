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

void		exit_get_out(t_env *env, t_list *lst, t_user *start, int status)
{
	(void)lst;
	ft_printf("exit\n");
	free_all(start);
	free(start);
	free_double_tab(env->tab);
	free(env);
	exit(status);
}

int			numeric_arg(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (-1);
		i++;
	}
	return (0);
}

int			exit_arg_check(t_list *lst)
{
	int i;

	while (lst->tab_cmd[i])
	{
		numeric_arg(lst->tab_cmd[i]);
		i++;
	}
	return (0);
}

void		ft_exit(t_env *env, t_list *lst, t_user *start)
{
	(void)env;
	if (double_tab_size(lst->tab_cmd) == 1)
		exit_get_out(env, lst, start, 0);
	else if (numeric_arg(lst->tab_cmd[1]) == 0
			&& double_tab_size(lst->tab_cmd) == 2)
		exit_get_out(env, lst, start, ft_atoi(lst->tab_cmd[1]));
	else if (numeric_arg(lst->tab_cmd[1]) == 0
			&& double_tab_size(lst->tab_cmd) > 2)
		ft_printf("bash: exit: trop d'arguments\n");
	else
	{
		ft_printf("bash: exit: %s : argument numérique nécessaire\n",
		lst->tab_cmd[1]);
		exit_get_out(env, lst, start, 2);
	}
}
