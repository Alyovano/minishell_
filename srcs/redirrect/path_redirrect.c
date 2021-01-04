/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_redirrect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:36:15 by user42            #+#    #+#             */
/*   Updated: 2021/01/04 11:08:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_file(char *str, int i, t_quote *quote)
{
	char	*tmp;
	int		j;

	j = 0;
	quote->token_in_dquote = -1;
	quote->token_in_simple_quote = -1;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	if (!tmp)
		malloc_error();
	while (str[i])
	{
		if (quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1 \
			&& (str[i] == '\'' ||  str[i] == '"') && get_backslash(str, i) == 0)
		{
			if (str[i] == '\'')
				quote->token_in_simple_quote *= -1;
			else
				quote->token_in_dquote *= -1;
			i++;
		}
		else if (quote->token_in_dquote == 1 && str[i] == '"' && get_backslash(str, i) == 0)
		{
			quote->token_in_dquote *= -1;
			i++;
			if (str[i] == ' ' || str[i] == '\0')
			{
				tmp[j] = '\0';
				return (tmp);
			}
		}
		else if (quote->token_in_simple_quote == 1 && str[i] == '\'' && get_backslash(str, i) == 0)
		{
			quote->token_in_simple_quote *= -1;
			i++;
			if (str[i] == ' ' || str[i] == '\0')
			{
				tmp[j] = '\0';
				return (tmp);
			}
		}
		else if (quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1 \
			&& (str[i] == ' ' || str[i] == '>' || str[i] == '<'))
		{
			tmp[j] = '\0';
			return (tmp);
		}
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

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
	file_name = get_file(str, i , &quote);
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
	file_name = get_file(str, i , &quote);
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
