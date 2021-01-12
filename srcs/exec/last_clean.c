/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:47:44 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 13:42:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		realloc_clean2(char *str, char **ret, int *j, t_quote *q)
{
	int i;

	i = 0;
	if (str[i] == '\'' && get_backslash(str, i) == 0 && q->dquote == -1)
	{
		q->squote *= -1;
		i++;
		while (str[i] && q->squote == 1 && str[i] != '\'')
			(*ret)[(*j)++] = str[i++];
	}
	else if (str[i] == '\\')
	{
		if (q->dquote == -1)
			(*ret)[(*j)++] = str[++i];
		else if (!(q->dquote == 1 && (str[i + 1] == '\\' || \
						str[i + 1] == '$' || str[i + 1] == '"')))
			(*ret)[(*j)++] = str[i];
	}
	else
		(*ret)[(*j)++] = str[i];
	return (i);
}

char	*realloc_clean(char *str, int size)
{
	int		i;
	int		j;
	char	*ret;
	t_quote	q;

	i = -1;
	j = 0;
	q.squote = -1;
	q.dquote = -1;
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		malloc_error();
	while (str[++i])
	{
		if (str[i] == '"' && get_backslash(str, i) == 0)
			q.dquote *= -1;
		else
			i += realloc_clean2(str + i, &ret, &j, &q);
	}
	ret[j] = '\0';
	return (ret);
}

void	get_nb_clean2(char *str, t_quote *q, int *i, int *len)
{
	if (str[*i] == '"' && get_backslash(str, *i) == 0)
	{
		q->dquote *= -1;
		(*len)--;
	}
	else if (str[*i] == '\'' && get_backslash(str, *i) == 0)
	{
		q->squote *= -1;
		*len -= 2;
		(*i)++;
		while (str[*i] && q->squote == 1 && str[*i] != '\'')
			(*i)++;
	}
	else if (str[*i] == '\\')
	{
		if (q->dquote == -1)
		{
			(*len)--;
			(*i)++;
		}
		else if (q->dquote == 1 && (str[*i + 1] == '\\' || str[*i + 1] == '$' \
													|| str[*i + 1] == '"'))
			(*len)--;
	}
}

int		get_nb_clean(char *str)
{
	int		i;
	int		len;
	t_quote	q;

	i = -1;
	len = ft_strlen(str);
	q.squote = -1;
	q.dquote = -1;
	while (str[++i])
		get_nb_clean2(str, &q, &i, &len);
	return (len);
}

int		last_clean(t_list *lst)
{
	int		i;
	char	*tmp;
	int		size;

	while (lst)
	{
		i = -1;
		while (lst->tab_cmd[++i])
		{
			if (find_char(lst->tab_cmd[i], '"') || \
		find_char(lst->tab_cmd[i], '\'') || find_char(lst->tab_cmd[i], '\\'))
			{
				size = get_nb_clean(lst->tab_cmd[i]);
				if ((size_t)size != ft_strlen(lst->tab_cmd[i]))
				{
					tmp = realloc_clean(lst->tab_cmd[i], size);
					free(lst->tab_cmd[i]);
					lst->tab_cmd[i] = ft_strdup(tmp);
					free(tmp);
				}
			}
		}
		lst = lst->next;
	}
	return (0);
}
