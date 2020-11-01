/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2020/11/01 13:26:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Fonction qui va dispatch vers builtin ou execve
*/

int		dispatch_cmd(t_list *lst)
{
	while (lst)
	{
		/*
		if (ft_strncmp("echo", lst->builtin, ft_strlen(lst->builtin)))
			//appel fonction builtin
		else if (ft_strncmp("cd", lst->builtin, ft_strlen(lst->builtin)))
			//appel fonction builtin
		else if (ft_strncmp("pwd", lst->builtin, ft_strlen(lst->builtin)))
			//appel fonction builtin
		else if (ft_strncmp("export", lst->builtin, ft_strlen(lst->builtin)))
			//appel fonction builtin
		else if (ft_strncmp("unset", lst->builtin, ft_strlen(lst->builtin)))
			//appel fonction builtin
		else if (ft_strncmp("env", lst->builtin, ft_strlen(lst->builtin)))
			//appel fonction builtin
		else if (ft_strncmp("exit", lst->builtin, ft_strlen(lst->builtin)))
			//appel fonction builtin
		else
			//appel execve (mais il faut gérer la gestion des pipes, je bossse actuellement ici)
			*/
		lst = lst->next;
	}	
	return (1);
}