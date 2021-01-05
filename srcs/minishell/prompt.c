/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 11:37:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_strcpy_prompt(char *dst, const char *src)
{
	char	*dest;
	size_t	i;

	dest = dst;
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dst);
}

char		*cat_prompt_cwd(char *s1, const char *s2)
{
	ft_strcpy_prompt(s1 + (ft_strlen((const char*)s1)), s2);
	return (s1);
}

void		print_promt(char *cwd)
{
	if (cwd)
	{
		ft_putstr_color("[", "\033[1;34m");
		ft_putstr_color(cwd, "\033[1;34m");
		ft_putstr_color("] ", "\033[1;34m");
		cat_prompt_cwd(cwd, "/");
		ft_putstr_color(" » ", "\033[0;31m");
	}
	else
		ft_putstr_color(" » ", "\033[0;31m");
}

void		prompt(void)
{
	char *tmp;

	g_reg = 0;
	if (g_reg == 0)
	{
		tmp = getcwd(NULL, 0);
		if (tmp)
		{
			ft_putstr_color("[", "\033[1;34m");
			ft_putstr_color(tmp, "\033[1;34m");
			ft_putstr_color("] ", "\033[1;34m");
			cat_prompt_cwd(tmp, "/");
			ft_putstr_color(" » ", "\033[0;31m");
		}
		else
			ft_putstr_color(" » ", "\033[0;31m");
		free(tmp);
	}
}
