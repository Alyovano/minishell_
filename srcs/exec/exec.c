/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:14:42 by user42            #+#    #+#             */
/*   Updated: 2020/11/17 10:04:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Fonction ayant pour unique but de tester
// pour le moment

/*
** Ajout du flag dans execve pour tester le comportement
*/

int         exec_execve(t_list *lst, char **env)
{
	struct stat		test;
	char			*path;
	char 			*exec_arg[4];

	path = ft_strjoin("/bin/", lst->builtin);
	if (stat(path, &test) != -1)
	{
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
		if (execve(path, exec_arg, env) == -1)
			return (-2);		//error with execve
	}
	else
		return (-1);	//cmd not found in /bin/
	return (0);
}

/*
** fork() permet de dupliquer un processus
** il crée donc un processus enfant en plus du processus parent déjà esistant
** à partir de l'appel de fork, la duplication commence
** le processus enfant à un pid (processus ID) == 0
** Du coup quand on apelle execve le programme ne s'arrète plus (vu qu'on est dans le process enfant)
*/

int		exec_solo(t_list *lst, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		// Child process
		if (dispatch_cmd(lst, env) == -1)
		{
			error_output_token(-6, lst->builtin);
			return (-1);	//cmd not found in /bin/
		}
	}
	else if (pid < 0)
	{
		// Fork error
		return (-2);
	}
	else
	{
		// Parent process
		waitpid(pid, &status, WCONTINUED | WUNTRACED);
  	}
	return 1;
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
		if (ft_lstsize(lst) > 1)
			exec_pipe(lst, env->tab, ft_lstsize(lst));
		else
			exec_solo(lst, env->tab);
		start->line = start->line->next;
	}
	start->line = ptr;
    return (0);
}
