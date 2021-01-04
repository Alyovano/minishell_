/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_redirrect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:36:15 by user42            #+#    #+#             */
/*   Updated: 2021/01/04 15:09:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_file_return(int j, char *tmp)
{
	tmp[j] = '\0';
	return (tmp);
}

void	get_file_init(int *j, char **tmp, t_quote *q, char *str)
{
	*j = 0;
	q->t_in_dquote = -1;
	q->t_in_squote = -1;
	*tmp = malloc(sizeof(char) * ft_strlen(str));
	if (!(*tmp))
		malloc_error();
}

char	*get_file(char *str, int i, t_quote *q)
{
	char	*tmp;
	int		j;

	get_file_init(&j, &tmp, q, str);
	while (str[i])
	{
		if (q->t_in_dquote == -1 && q->t_in_squote == -1 \
			&& (str[i] == '\'' || str[i] == '"') && get_backslash(str, i) == 0)
		{
			if (str[i++] == '\'')
				q->t_in_squote *= -1;
			else
				q->t_in_dquote *= -1;
		}
		else if (q->t_in_dquote == 1 && str[i] == '"' && \
												get_backslash(str, i) == 0)
		{
			q->t_in_dquote *= -1;
			if (str[++i] == ' ' || str[i] == '\0')
				return (get_file_return(j, tmp));
		}
		else if (q->t_in_squote == 1 && str[i] == '\'' \
											&& get_backslash(str, i) == 0)
		{
			q->t_in_squote *= -1;
			if (str[++i] == ' ' || str[i] == '\0')
				return (get_file_return(j, tmp));
		}
		else if (q->t_in_dquote == -1 && q->t_in_squote == -1 \
			&& (str[i] == ' ' || str[i] == '>' || str[i] == '<'))
			return (get_file_return(j, tmp));
		else
			tmp[j++] = str[i++];
	}
	return (get_file_return(j, tmp));
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
	file_name = get_file(str, i, &quote);
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
	file_name = get_file(str, i, &quote);
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
