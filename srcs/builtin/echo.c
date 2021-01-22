/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/11 13:24:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define FLAG_OK 0
#define FLAG_FAILURE 1
#define NO_FLAG 2

int			check_echo_flag(char *str)
{
	unsigned int i;

	i = 1;
	if (str == NULL)
		return (NO_FLAG);
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			i++;
	}
	else
		return (NO_FLAG);
	if (i == ft_strlen(str))
		return (FLAG_OK);
	return (FLAG_FAILURE);
}

void		echo_print(t_list *lst, int i)
{
	while (lst->tab_cmd[i])
	{
		if (lst->tab_cmd[i + 1] == NULL)
			ft_printf("%s", lst->tab_cmd[i]);
		else
			ft_printf("%s ", lst->tab_cmd[i]);
		i++;
	}
}

int			ft_echo(t_env *env, t_list *lst)
{
	int flag;
	int i;

	(void)env;
	flag = check_echo_flag(lst->tab_cmd[1]);
	i = 0;
	if (flag == FLAG_OK)
	{
		i = 1;
		while (check_echo_flag(lst->tab_cmd[i]) == FLAG_OK)
			i++;
		echo_print(lst, i);
		return (0);
	}
	else if (flag == FLAG_FAILURE || flag == NO_FLAG)
	{
		i = 1;
		echo_print(lst, i);
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}
