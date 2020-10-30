/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:52:44 by user42            #+#    #+#             */
/*   Updated: 2020/10/30 20:27:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_quote(char **str)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	
	j = 0;
	i = 0;
	len = ft_strlen(*str);
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
			len--;
		i++;
	}
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		exit(-1);
	i = 0;
	while ((*str)[i])
	{
		if (!((*str)[i] == '"' || (*str)[i] == '\''))
		{
			tmp[j] = (*str)[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	free(*str);
	*str = tmp;
}

int		valid_and_clean_builtin(t_list *lst)
{
	if (find_char(lst->builtin, '"') || find_char(lst->builtin, '\''))
		clean_quote(&lst->builtin);
	if (find_char(lst->builtin, ' ') == 1)
		return (-1);
	return (1);
}
