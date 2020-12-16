/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:14:42 by user42            #+#    #+#             */
/*   Updated: 2020/12/16 15:51:08 by user42           ###   ########.fr       */
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
	paths = ft_split(path + 5, ':');
	free(path);
	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, builtin);
		free(temp);
		free(paths[i]);
		paths[i] = ft_strdup(path);
		free(path);
		i++;
	}
	return (paths);
}

char		*check_path(char **paths)
{
	struct stat		test;
	int				i;

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

int         exec_execve(t_list *lst, t_env *env)
{
	char	*path;
	char 	*exec_arg[4];

	path = check_path(get_path(env->tab, lst->builtin));
	if (path == NULL)
		return (-1);	//cmd not found in /bin/
	exec_arg[0] = lst->builtin;
	if (lst->argu == NULL || ft_strncmp(lst->argu, "", 1) == 0) //temp fix
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
		return (-2); //error with execve
	return (0);
}

/*
** Fonction exectution qui clean les builtins et faire le parsing des flags
** puis execute les commandes
*/

int		 execution(t_user *start, t_env *env)
{
	void	*ptr;
	t_list	*lst;

    ptr = start->line;
    while (start->line)
    {
		lst = start->line->content;
		clean_builtin(lst);
		parse_flags(lst);
		clean_args(lst);
		//debug(lst);
		if (ft_strcmp("exit", lst->builtin) == 0)
			ft_exit(env, lst, start);
		else if (exec_main(lst, env) == -1)
			return (-1);
		start->line = start->line->next;		
	}
	start->line = ptr;
    return (0);
}
