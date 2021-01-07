/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:14:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 13:21:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**get_path(char **env, char *builtin)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	path = NULL;
	while (env[i] && path == NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' \
									&& env[i][3] == 'H' && env[i][4] == '=')
			path = ft_strdup(env[i]);
		i++;
	}
	if (path == NULL)
		return (NULL);
	paths = ft_split(path + 5, ':');
	free(path);
	if (paths[0] == NULL)
	{
		free(paths);
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			temp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(temp, builtin);
			free(temp);
		}
		else
		{
			temp = ft_strdup(paths[i]);
			path = ft_strjoin(temp, builtin);
			free(temp);
		}
		free(paths[i]);
		paths[i] = ft_strdup(path);
		free(path);
		i++;
	}
	return (paths);
}

char		*check_path(char **paths, char *path)
{
	struct stat		test;
	int				i;

	if (path != NULL)
	{
		if (stat(path, &test) != -1)
			return (path);
		return (NULL);
	}
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (stat(paths[i], &test) != -1)
			return (paths[i]);
		i++;
	}
	return (NULL);
}

/*
** Ajout du flag dans execve pour tester le comportement
*/

int		exec_execve(t_list *lst, t_env *env, char *path)
{
	char	*exec_arg[4];

	exec_arg[0] = lst->builtin;
	if (lst->argu == NULL || ft_strcmp(lst->argu, "") == 0)
	{
		if (lst->flag)
		{
			exec_arg[1] = lst->flag;
			exec_arg[2] = NULL;
		}
		else
			exec_arg[1] = NULL;
	}
	else if (lst->flag)
	{
		exec_arg[1] = lst->flag;
		exec_arg[2] = lst->argu;
		exec_arg[3] = NULL;
	}
	else
	{
		exec_arg[1] = lst->argu;
		exec_arg[2] = NULL;
	}
	if (execve(path, exec_arg, env->tab) == -1)
		return (-2);
	return (0);
}

/*
** Fonction exectution qui clean les builtins et faire le parsing des flags
** puis execute les commandes
** Debug with: debug(lst);
*/

int		execution(t_user *start, t_env *env)
{
	t_list	*lst;

	while (start->line)
	{
		lst = start->line->content;
		clean_builtin(lst);
		parse_flags(lst);
		clean_args(lst);
		if (ft_strcmp("exit", lst->builtin) == 0)
			ft_exit(env, lst, start);
		else if (exec_main(lst, env) == -1)
			return (-1);
		start->line = start->line->next;
	}
	return (0);
}
