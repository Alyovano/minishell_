/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:02:20 by alyovano          #+#    #+#             */
/*   Updated: 2021/01/26 14:52:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*finalstr;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (ft_strdup(!s1 ? s2 : s1));
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!((finalstr = malloc(sizeof(char) * (size1 + size2 + 1)))))
		malloc_error();
	ft_memcpy(finalstr, s1, size1);
	ft_memcpy(finalstr + size1, s2, size2);
	finalstr[size1 + size2] = '\0';
	return (finalstr);
}
