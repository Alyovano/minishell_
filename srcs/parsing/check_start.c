/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2020/10/22 13:20:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			check_input_start(t_user *start)
{
	int i;

	i = 0;
	while (start->user_input[i] && start->user_input[i] == ' ')
		i++;
	if (start->user_input[i] == ';')
		return (-1);
	if (start->user_input[i] == '>')
	{
		if (start->user_input[i + 1])
		{
			i++;
			while (start->user_input[i] && start->user_input[i] == ' ')
				i++;
			if (start->user_input[i] == ';')
				return (-1);
			if (!start->user_input[i])
				return (-4);
			if (start->user_input[i] != ' ')
				return (0);
		}
		return (-4);
	}
	return (0);
}
