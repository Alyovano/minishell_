/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 15:05:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		exit_get_out(t_env *env, t_list *lst, t_user *start,
									int status)
{
	(void)lst;
	free_all(start);
	free(start);
	free_double_tab(env->tab);
	free(env);
	if (status != 0)
		exit(status);
	else
		exit(g_errno);
}

int			numeric_arg(char *str)
{
	int i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
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
	ft_printf("exit\n");
	if (double_tab_size(lst->tab_cmd) == 1)
		exit_get_out(env, lst, start, 0);
	else if (numeric_arg(lst->tab_cmd[1]) == 0
			&& double_tab_size(lst->tab_cmd) == 2)
		exit_get_out(env, lst, start, ft_atoi(lst->tab_cmd[1]));
	else if (numeric_arg(lst->tab_cmd[1]) == 0
			&& double_tab_size(lst->tab_cmd) > 2)
	{
		ft_putstr_fd("bash: exit: trop d'arguments\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(lst->tab_cmd[1], STDERR_FILENO);
		ft_putstr_fd(" : argument numérique nécessaire\n", STDERR_FILENO);
		exit_get_out(env, lst, start, 2);
	}
}
