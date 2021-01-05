/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirrect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:51:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 09:18:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_redirrect(t_list *lst, t_quote *quote)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(lst->content);
	quote->t_in_dquote = -1;
	quote->t_in_squote = -1;
	while (tmp[i])
	{
		if (tmp[i] == '\'' && get_backslash(tmp, i) == 0)
			quote->t_in_squote *= -1;
		else if (tmp[i] == '"' && get_backslash(tmp, i) == 0)
			quote->t_in_dquote *= -1;
		else if ((tmp[i] == '>' || tmp[i] == '<') && get_backslash(tmp, i) == 0
			&& quote->t_in_dquote == -1 && quote->t_in_squote == -1)
			return (1);
		i++;
	}
	free(tmp);
	return (0);
}

void	next_quote(char *str, int *i)
{
	if (str[*i] == '\'' && get_backslash(str, *i) == 0)
	{
		(*i)++;
		while (str[*i] && !(str[*i] == '\'' && get_backslash(str, *i) == 0))
			(*i)++;
	}
	else if (str[*i] == '"' && get_backslash(str, *i) == 0)
	{
		(*i)++;
		while (str[*i] && !(str[*i] == '"' && get_backslash(str, *i) == 0))
			(*i)++;
	}
}

int		check_next_redirrect(int *i, char *tmp)
{
	if (tmp[*i] == '>' && tmp[*i + 1] == '>')
	{
		if (check_redirrect(tmp, *i + 2) == -1)
			return (-1);
	}
	else if (tmp[*i] == '<' && tmp[*i + 1] == '>')
	{
		if (check_redirrect(tmp, *i + 2) == -1)
			return (-1);
	}
	else if (tmp[*i] == '>')
	{
		if (check_redirrect(tmp, *i + 1) == -1)
			return (-1);
	}
	else if (tmp[*i] == '<')
	{
		if (check_redirrect(tmp, *i + 1) == -1)
			return (-1);
	}
	return (0);
}

int		get_redirrect2(int *i, char *tmp, t_list *lst)
{
	if (check_next_redirrect(i, tmp) == -1)
		return (-1);
	if (tmp[*i] == '>' && tmp[*i + 1] == '>')
	{
		(*i) += write_redirrect(tmp, *i + 2, lst, "APPEND");
		(*i)++;
	}
	else if (tmp[*i] == '<' && tmp[*i + 1] == '>')
	{
		(*i) += read_redirrect(tmp, *i + 2, lst, "READ_CREATE");
		(*i)++;
	}
	else if (tmp[*i] == '>')
	{
		(*i) += write_redirrect(tmp, *i + 1, lst, "WRITE");
	}
	else if (tmp[*i] == '<')
	{
		(*i) += read_redirrect(tmp, *i + 1, lst, "READ");
	}
	return (0);
}

int		get_redirrect(t_list *lst, t_quote *quote)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(lst->content);
	quote->t_in_dquote = -1;
	quote->t_in_squote = -1;
	if (redirrect_error(tmp) == -1)
		return (-1);
	while (tmp[i])
	{
		if ((tmp[i] == '\'' || tmp[i] == '"') && get_backslash(tmp, i) == 0)
		{
			next_quote(tmp, &i);
		}
		else if ((tmp[i] == '>' || tmp[i] == '<') && get_backslash(tmp, i) == 0)
		{
			if (get_redirrect2(&i, tmp, lst) == -1)
				return (-1);
		}
		i++;
	}
	free(tmp);
	return (1);
}
