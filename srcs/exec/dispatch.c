/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2020/12/17 09:04:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function pour savoir si la commande existe (ret 1) ou existe pas (ret 0)
*/

int		cmd_valididy(char *cmd, t_env *env)
{
	char		*path;

	path = check_path(get_path(env->tab, cmd), NULL);
	if (ft_strcmp(cmd, "echo") == 0 || \
		ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || \
		ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 || \
		ft_strcmp(cmd, "env") == 0 || \
		ft_strcmp(cmd, "exit") == 0 || \
		ft_strcmp(cmd, "$?") == 0)
		return (1);
	if (path != NULL)
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

/*
** Fonction qui va dispatch vers builtin ou execve
** le check d'erreur se fait au dernier moment dans la fonction cmd_validity
*/

int		dispatch_cmd(t_list *lst, t_env *env)
{
	int		ret;
	char	*path;

	ret = 0;
	if (ft_strcmp("export", lst->builtin) == 0)
	{
		ft_export(env, lst->argu);
	}
	else if (ft_strcmp("unset", lst->builtin) == 0)
	{
		ft_unset(env, lst->argu);
	}
	else if (ft_strcmp("pwd", lst->builtin) == 0)
	{
		ft_pwd();
	}
	else if (ft_strcmp("echo", lst->builtin) == 0)
	{
		ft_echo(env, lst);
	}
	else if (ft_strcmp("cd", lst->builtin) == 0)
	{
		ft_cd(env, lst->argu);
	}
	else if (ft_strcmp("env", lst->builtin) == 0)
	{
		ft_env(env, lst->argu);
	}
	else if (ft_strcmp("exit", lst->builtin) != 0)
	{
		path = check_path(get_path(env->tab, lst->builtin), NULL);
		ret = exec_execve(lst, env, path);
	}
	return (ret);
}