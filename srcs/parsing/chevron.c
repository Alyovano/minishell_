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

int			is_this_redirectable_reverse(t_user *start, t_quote *quote, int i)
{
	(void)quote;
	if (start->user_input[i] == '<')
	{
		if (start->user_input[i - 1] && start->user_input[i - 1] == '<'
		&& get_backslash(start->user_input, i - 1) == 0)
		{
			start->chevron_nb = -2;
			return (-1);
		}
	}
	return (1);
}

int			is_this_redirectable(t_user *start, t_quote *quote, int i)
{
	(void)quote;
	if (start->user_input[i] == '>')
	{
		if (start->user_input[i - 1] && start->user_input[i - 1] == '>')
		{
			if (start->user_input[i - 2] && start->user_input[i - 2] == '>'
			&& get_backslash(start->user_input, i - 2) == 0)
			{
				start->chevron_nb = 3;
				return (-1);
			}
		}
	}
	return (1);
}
