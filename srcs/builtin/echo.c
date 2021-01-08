/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:55:58 by user42           ###   ########.fr       */
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
	if (i == ft_strlen(str))
		return (FLAG_OK);
	return (FLAG_FAILURE);
}

int			ft_echo(t_env *env, t_list *lst)
{
	(void)env;
	int flag;
	int i;

	flag = check_echo_flag(lst->tab_cmd[1]);
	i = 0;
	if (flag == FLAG_OK)
	{
		i = 2;
		while (lst->tab_cmd[i])
		{
			if (lst->tab_cmd[i + 1] == NULL)
				ft_printf("%s", lst->tab_cmd[i]);
			else
				ft_printf("%s ", lst->tab_cmd[i]);
			i++;
		}
		//status = 0
		return (0);
	}
	else if (flag == FLAG_FAILURE)
	{
		i = 1;
		while (lst->tab_cmd[i])
		{
			if (lst->tab_cmd[i + 1] == NULL)
				ft_printf("%s", lst->tab_cmd[i]);
			else
				ft_printf("%s ", lst->tab_cmd[i]);
			i++;
		}
		write(1, "\n", 1);
		// status = 0;
		return (0);
	}
	//status = 1;
	return (1);
}
