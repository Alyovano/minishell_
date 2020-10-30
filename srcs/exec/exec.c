/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:14:42 by user42            #+#    #+#             */
/*   Updated: 2020/10/30 10:22:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Fonction ayant pour unique but de tester
// pour le moment

int         petite_execution(t_list *lst, char **env)
{
	struct stat		test;
	char			*path;
	char 			*exec_arg[3];

	path = ft_strjoin("/bin/", lst->builtin);
	if (stat(path, &test) != -1)
	{
		exec_arg[0] = lst->builtin;
 		exec_arg[1] = lst->argu;
		exec_arg[2] = NULL;
		if (execve(path, exec_arg, env) == -1)
			return (-1);
	}
	return (0);
}

/*
** fork() permet de dupliquer un processus
** il crée donc un processus enfant en plus du processus parent déjà esistant
** à partir de l'appel de fork, la duplication commence
** le processus enfant à un pid (processus ID) == 0
** Du coup quand on apelle execve le programme ne s'arrète plus (vu qu'on est dans le process enfant)
*/

int		launch_exec(t_list *lst, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		// Child process
		if (petite_execution(lst, env) == -1) 
			return (-1);
	}
	else if (pid < 0)
	{
		// Fork error
		return (-1);
	}
	else
	{
		// Parent process
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
  	}
	return 1;
}


int         execuction_temporaire(t_user *start)
{
    void	*ptr;
	
    ptr = start->line;
    while (start->line)
    {
		if (launch_exec(start->line->content, start->user_env) == -1)
			return (-1);
		//petite_execution(start->line->content, start->user_env);
        //debug(start->line->content);
        start->line = start->line->next;
    }
	
    start->line = ptr;
    return (0);
}