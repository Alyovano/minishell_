/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:52:44 by user42            #+#    #+#             */
/*   Updated: 2021/01/11 15:27:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		clean_end_spaces(char **str)
{
	int		i;
	char	*tmp;

	i = ft_strlen(*str) - 1;
	while ((*str)[i] && (*str)[i] == ' ')
		i--;
	tmp = ft_str_n_dup(*str, i + 1);
	free(*str);
	*str = tmp;
}

void	clean_quote(char **str)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	j = 0;
	i = -1;
	len = ft_strlen(*str);
	while ((*str)[++i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
			len--;
	}
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		exit(-1);
	i = -1;
	while ((*str)[++i])
	{
		if (!((*str)[i] == '"' || (*str)[i] == '\''))
			tmp[j++] = (*str)[i];
	}
	tmp[j] = '\0';
	free(*str);
	*str = tmp;
}

void	clean_builtin(t_list *lst)
{
	while (lst && lst->tab_cmd[0])
	{
		if (find_char(lst->tab_cmd[0], '"') || find_char(lst->tab_cmd[0], '\''))
			clean_quote(&lst->tab_cmd[0]);
		clean_end_spaces(&lst->tab_cmd[0]);
		lst = lst->next;
	}
}
