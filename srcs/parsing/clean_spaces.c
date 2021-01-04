/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 10:45:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/04 13:57:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function to know if string ends with whitespaces or not
** 1 == yes | 2 == no
*/

int		end_spaces(char *str, int i)
{
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/*
** Function to get clean string without white spaces
*/

void	get_clean_line(char *str, t_quote *quote, char **ret)
{
	int i;
	int j;

	i = 0;
	j = 0;
	quote->t_in_squote = -1;
	quote->t_in_dquote = -1;
	while (str[i])
	{
		if (str[i] == '\'' && (get_backslash(str, i) == 0))
			quote->t_in_squote *= -1;
		if (str[i] == '"' && (get_backslash(str, i) == 0))
			quote->t_in_dquote *= -1;
		if (quote->t_in_dquote == 1 || quote->t_in_squote == 1)
			(*ret)[j++] = str[i];
		else
		{
			if (!(((str[i] == ' ' && (str[i - 1] == ' ' || \
					i == 0 || str[i + 1] == '\0'))) || end_spaces(str, i)))
				(*ret)[j++] = str[i];
		}
		i++;
	}
	(*ret)[j] = '\0';
}

/*
** Function to know the length of string without spaces
** ex. "Hi  "  o"       " --> 8
*/

int		get_good_len(char *str, t_quote *quote)
{
	int i;
	int len;

	i = 0;
	len = 0;
	quote->t_in_squote = -1;
	quote->t_in_dquote = -1;
	while (str[i])
	{
		if (str[i] == '\'' && (get_backslash(str, i) == 0))
			quote->t_in_squote *= -1;
		if (str[i] == '"' && (get_backslash(str, i) == 0))
			quote->t_in_dquote *= -1;
		if (quote->t_in_dquote == 1 || quote->t_in_squote == 1)
			len++;
		else
		{
			if (!(((str[i] == ' ' && (str[i - 1] == ' ' || \
					i == 0 || str[i + 1] == '\0'))) || end_spaces(str, i)))
				len++;
		}
		i++;
	}
	return (len);
}

void	clean_spaces(t_user *start, t_quote *quote)
{
	int		i;
	char	*temp;

	i = 0;
	while (start->user_cmd_tab[i])
	{
		temp = malloc(sizeof(char) * \
				(get_good_len(start->user_cmd_tab[i], quote) + 1));
		get_clean_line(start->user_cmd_tab[i], quote, &temp);
		free(start->user_cmd_tab[i]);
		start->user_cmd_tab[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
}
