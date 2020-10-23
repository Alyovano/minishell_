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

int		get_clean_index(char *str)
{
	int i;

	i = 0;
	while (str[i] && (str[i] ==  ' ' || str[i] == ';'))
		i++;
	return (i);
}

/*
** Function to clean ';' from the line. Called in first_split.c
** Remove also empty string "echo ;" ==> [echo] [] ==> [echo]
*/

void	clean_line(t_user *start, t_quote *quote)
{
	int i;
	char *tmp;
	
	i = 1;
	while (start->user_cmd_tab[i])
	{
		tmp = ft_strdup(start->user_cmd_tab[i]);
		free(start->user_cmd_tab[i]);
		start->user_cmd_tab[i] = ft_substr(tmp, \
						get_clean_index(tmp), ft_strlen(tmp));
		free(tmp);
		i++;
	}
	if (start->user_cmd_tab[i - 1] && \
				start->user_cmd_tab[i - 1][0] == '\0')
	{
		free(start->user_cmd_tab[i - 1]);
		start->user_cmd_tab[i - 1] = NULL;
	}
	clean_spaces(start, quote);
}