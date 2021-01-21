/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 14:33:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				is_valid_char(char c)
{
	if (c == '[' || c == ']' || c == '!'
		|| c == '@' || c == '#' || c == '$' || c == '%'
		|| c == '^' || c == '&' || c == '*' || c == '{'
		|| c == '}' || c == '.' || c == ',' || c == '?'
		|| c == ':' || c == '\\')
		{
			g_errno = 1;
			return (-1);
		}
	return (0);
}

int				check_arg_nb(char *arg)
{
	int i;
	int nb;
	int token;

	i = 0;
	nb = 0;
	token = 0;
	while (arg[i])
	{
		token = 0;
		while (arg[i] && arg[i] != ' ')
		{
			if ((arg[i] == '"' || arg[i] == '\'') && get_backslash(arg, i) == 0)
				i += quote_len(arg + i);
			token = 1;
			i++;
		}
		if (token == 1)
			nb += 1;
		i++;
	}
	return (nb);
}

char			*clear_arg(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (str[i] == ' ')
		i += 1;
	while (str[i])
	{
		tmp[j] = str[i];
		if (str[i] == '\'' && get_backslash(str, i) == 0)
			tmp[j] = '"';
		i++;
		j++;
	}
	tmp[j] = 0;
	free(str);
	return (tmp);
}

/*
** Si un arg a un = mais pas de valeur ensuite
*/

char			**parsing_arg(char **arg_tab)
{
	char	*tmp;
	int		i;

	i = 0;
	while (arg_tab[i])
	{
		arg_tab[i] = first_clear_arg(arg_tab[i]);
		if (arg_tab[i][ft_strlen(arg_tab[i]) - 1] == '='
		&& arg_tab[i][ft_strlen(arg_tab[i])] == '\0')
		{
			tmp = ft_strjoin(arg_tab[i], "\"\"");
			free(arg_tab[i]);
			arg_tab[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (arg_tab);
}

char			*first_clear_arg(char *str)
{
	char *tmp;

	tmp = clear_arg(str);
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}
