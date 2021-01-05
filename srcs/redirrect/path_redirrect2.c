/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_redirrect2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:51:35 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 10:52:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** write_redirrect
** add file path to lst->out
** add type to lst->out_type
*/

int		write_redirrect(char *str, int i, t_list *lst, char *type)
{
	char	*file_name;
	char	**tmp;
	int		len;
	t_quote	quote;

	if (str[i] == ' ')
		i++;
	tmp = NULL;
	file_name = get_file(str, i, 0, &quote);
	tmp = add_str_to_tab(lst->out, file_name);
	free_double_tab(lst->out);
	lst->out = copy_double_tab(tmp);
	free_double_tab(tmp);
	len = ft_strlen(file_name);
	free(file_name);
	tmp = add_str_to_tab(lst->out_types, type);
	free_double_tab(lst->out_types);
	lst->out_types = copy_double_tab(tmp);
	free_double_tab(tmp);
	return (len);
}

/*
** read_redirrect
** add file path to lst->in
** add type to lst->in_type
*/

int		read_redirrect(char *str, int i, t_list *lst, char *type)
{
	char	*file_name;
	char	**tmp;
	int		len;
	t_quote	quote;

	if (str[i] == ' ')
		i++;
	file_name = get_file(str, i, 0, &quote);
	tmp = add_str_to_tab(lst->in, file_name);
	free_double_tab(lst->in);
	lst->in = copy_double_tab(tmp);
	free_double_tab(tmp);
	len = ft_strlen(file_name);
	free(file_name);
	tmp = add_str_to_tab(lst->in_types, type);
	free_double_tab(lst->in_types);
	lst->in_types = copy_double_tab(tmp);
	free_double_tab(tmp);
	return (len);
}
