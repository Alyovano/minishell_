/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 11:12:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Fonction qui va dispatch vers builtin ou execve
*/

int		dispatch_cmd(t_list *lst, char **env)
{
	if (ft_strncmp("valeur temporaire pour mute l'appel", lst->builtin, ft_strlen(lst->builtin)))
		ft_printf("appel fonction builtin\n");
	else
		petite_execution(lst, env);
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
	return (1);
}