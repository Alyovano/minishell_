/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:20:17 by user42            #+#    #+#             */
/*   Updated: 2021/01/18 10:30:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				find_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
** Function to split start->user_cmd_tab[i] with '|'
** Split is stored to start->line (type t_list)
** In each t_list->content there is another t_list
** ex. minishell> echo hello | grep -e ; echo lol
** t_list lst1->content = echo hello
** t_list lst1->content = grep -e
** t_list lst2->content = echo lol
** t_lsit start_line-> content = lst1, lst2
*/

void			split_pipe(t_user *start, t_quote *quote)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (start->user_cmd_tab[i])
	{
		tmp = cut_input_to_tab_pipe(quote, start->user_cmd_tab[i]);
		if (i == 0)
			start->line = ft_lstnew(tmp);
		else
		{
			ft_lstadd_back(&start->line, ft_lstnew(tmp));
		}
		i++;
	}
}
