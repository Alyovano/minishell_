/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2020/11/17 10:11:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function pour savoir si la commande existe (ret 1) ou existe pas (ret 0)
*/

int		cmd_valididy(char *cmd)
{
	struct stat	test;
	char		*path;

	path = ft_strjoin("/bin/", cmd);
	if (ft_strcmp(cmd, "echo") == 0 || \
		ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || \
		ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 || \
		ft_strcmp(cmd, "env") == 0 || \
		ft_strcmp(cmd, "exit") == 0 || \
		ft_strcmp(cmd, "$?") == 0)
		return (1);
	if (stat(path, &test) != -1)
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

int		dispatch_cmd(t_list *lst, t_env *env, t_user *start)
{
	(void)start;
	int ret;

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
	else if (ft_strcmp("exit", lst->builtin) == 0)
	{
		ft_exit(env, lst, start);
		//cette fonction doit monter plus haut, ici elle marche pas
	}
	else if (ft_strcmp("cd", lst->builtin) == 0)
	{
		ft_cd(env, lst->argu);
	}
	else if (ft_strcmp("env", lst->builtin) == 0)
	{
		ft_env(env, lst->argu);
	}
	else
		ret = exec_execve(lst, env->tab);	
	return (ret);
}