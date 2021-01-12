/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_realloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:20:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 15:33:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		tokenize_space_index(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

/*
** Return 1: if str == '\0' or str contains only spaces
** Return 0: in other cases
*/

int		is_space_empty(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

char	**tokenize_realloc2(int *i, int *j, int *size, char **tab)
{
	char	**ret;

	*size = 0;
	*i = -1;
	*j = 0;
	while (tab[++(*i)])
	{
		if (is_space_empty(tab[*i]) == 0)
			(*size)++;
	}
	ret = malloc(sizeof(char *) * (*size + 1));
	if (!ret)
		malloc_error();
	*i = -1;
	return (ret);
}

/*
** Function to remove empty elements in tab
** also remove only space elements
*/

char	**tokenize_realloc(char **tab)
{
	int		size;
	int		i;
	int		j;
	char	**ret;

	ret = tokenize_realloc2(&i, &j, &size, tab);
	while (tab[++i])
	{
		if (is_space_empty(tab[i]) == 0)
		{
			size = tokenize_space_index(tab[i]);
			if (size == 0)
				ret[j] = ft_strdup(tab[i]);
			else
				ret[j] = ft_substr(tab[i], size, ft_strlen(tab[i]));
			j++;
		}
	}
	ret[j] = NULL;
	return (ret);
}
