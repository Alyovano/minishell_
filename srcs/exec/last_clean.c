/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:47:44 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 12:43:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*realloc_clean(char *str, t_quote *q, int size)
{
	int		i;
	int		j;
	int len = 0;
	char	*ret;

	i = 0;
	j = 0;
	q->squote = -1;
	q->dquote = -1;
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		malloc_error();
	while (str[i])
	{
		if (str[i] == '"' && get_backslash(str, i) == 0)
		{
			q->dquote *= -1;
			len--;
		}
		else if (str[i] == '\'' && get_backslash(str, i) == 0 && q->dquote == -1)
		{
			q->squote *= -1;
			len--;
			i++;
			while (str[i] && q->squote == 1 && str[i] != '\'')
				ret[j++] = str[i++];
			len--;
			
		}
		else if (str[i] == '\\')
		{
			if (q->dquote == -1)
			 {
				len--;
				ret[j++] = str[++i];
			 }				
			else if (q->dquote == 1 && (str[i + 1] == '\\' || str[i + 1] == '$'))
				len--;
			else
				ret[j++] = str[i];
		}
		else
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int		get_nb_clean(char *str, t_quote *q)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	q->squote = -1;
	q->dquote = -1;
	while (str[i])
	{
		if (str[i] == '"' && get_backslash(str, i) == 0)
		{
			q->dquote *= -1;
			len--;
		}
		else if (str[i] == '\'' && get_backslash(str, i) == 0)
		{
			q->squote *= -1;
			len--;
			i++;
			while (str[i] && q->squote == 1 && str[i] != '\'')
				i++;
			len--;
			
		}
		else if (str[i] == '\\')
		{
			if (q->dquote == -1)
			 {
				len--;
				i++;
			 }				
			else if (q->dquote == 1 && (str[i + 1] == '\\' || str[i + 1] == '$'))
				len--;
		}
		i++;
	}
	return (len);
}

int		last_clean(t_list *lst)
{
	int		i;
	char	*tmp;
	int		size;
	t_quote	q;

	while (lst)
	{
		i = 0;
		while (lst->tab_cmd[i])
		{
			//clean
			if (find_char(lst->tab_cmd[i], '"') || find_char(lst->tab_cmd[i], '\'') \
										|| find_char(lst->tab_cmd[i], '\\'))
			{
				size = get_nb_clean(lst->tab_cmd[i], &q);
				if ((size_t)size != ft_strlen(lst->tab_cmd[i]))
				{
					tmp = realloc_clean(lst->tab_cmd[i], &q, size);
					free(lst->tab_cmd[i]);
					lst->tab_cmd[i] = ft_strdup(tmp);
					free(tmp);
				}
			}
			i++;
		}
		lst = lst->next;
	}
	return (0);
}
