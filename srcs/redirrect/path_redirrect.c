/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_redirrect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:36:15 by user42            #+#    #+#             */
/*   Updated: 2020/12/11 09:40:18 by user42           ###   ########.fr       */
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
		if (quote->token_in_dquote == 1 && str[i] == '"' && get_backslash(str, i) == 0)
		{
			quote->token_in_dquote *= -1;
			i++;
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
			{
				tmp[++j] = '\0';
				return (tmp);
			}
		}
		else if (quote->token_in_simple_quote == 1 && str[i] == '\'' && get_backslash(str, i) == 0)
		{
			quote->token_in_simple_quote *= -1;
			i++;
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
			{
				tmp[++j] = '\0';
				return (tmp);
			}
		}
		if (quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1 \
			&& str[i] == ' ')
		{
			tmp[++j] = '\0';
			return (tmp);
		}
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

/*
** Return file path (file name with pwd)
*/

char	*get_file_path(char *str, int i, t_quote *quote)
{
	char	*file_name;
	char	*file_path;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		malloc_error();
	file_name = get_file(str, i , quote);
	if (strcmp(pwd, "/") != 0)
	{
		tmp = ft_strdup(file_name);
		file_name = ft_strjoin("/", tmp);
		free(tmp);
	}
	file_path = ft_strjoin(pwd, file_name);
	free(pwd);
	free(file_name);
	return (file_path);
}

/*
** write_redirrect
** add file path to lst->out
** add type to lst->out_type
*/

void	write_redirrect(char *str, int i, t_list *lst, char *type)
{
	char	*file_path;
	char	**tmp;
	t_quote	quote;

	if (str[i] == ' ')
		i++;
	file_path = get_file_path(str, i, &quote);
	tmp = add_str_to_tab(lst->out, file_path);
	free_double_tab(lst->out);
	lst->out = copy_double_tab(tmp);
	free_double_tab(tmp);
	free(file_path);
	tmp = add_str_to_tab(lst->out_types, type);
	free_double_tab(lst->out_types);
	lst->out_types = copy_double_tab(tmp);
	free_double_tab(tmp);
}

/*
** read_redirrect
** add file path to lst->in
** add type to lst->in_type
*/

void	read_redirrect(char *str, int i, t_list *lst, char *type)
{
	char	*file_path;
	char	**tmp;
	t_quote	quote;

	if (str[i] == ' ')
		i++;
	file_path = get_file_path(str, i, &quote);
	tmp = add_str_to_tab(lst->in, file_path);
	free_double_tab(lst->in);
	lst->in = copy_double_tab(tmp);
	free_double_tab(tmp);
	free(file_path);
	tmp = add_str_to_tab(lst->in_types, type);
	free_double_tab(lst->in_types);
	lst->in_types = copy_double_tab(tmp);
	free_double_tab(tmp);
}
