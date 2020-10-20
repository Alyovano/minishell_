/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:26:17 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 10:53:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_clean_index(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] ==  " " || str[i] == ";")
		i++;
	return (i);
}

void clean_line(t_user *start)
{
	int i;
	char temp;

	i = 1; //le premier n'a jamais de ";"
	while (start->user_cmd_tab[i])
	{
		i++;
	}
}