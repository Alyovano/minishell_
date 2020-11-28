/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:40:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/17 10:22:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && i < ft_strlen(s2))
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

int		exec_fork(t_list *lst, t_env *env, int old_fd[2], t_user *start)
{
	pipe(lst->fd);
	if ((lst->pid = fork()) == -1)
		return (-1);
	else if (lst->pid == 0)
	{
		//child process
		if (lst->stdout_fd)
		{
			dup2(lst->fd[1], STDOUT_FILENO);
			close(lst->fd[0]);
		}
		if (lst->stdin_fd)
		{
			dup2(old_fd[0], STDIN_FILENO);
			close(old_fd[1]);
		}
		dispatch_cmd(lst, env, start);
		exit(0);
	}
	close(lst->fd[1]);
	return (1);
}

int		exec_pipe(t_list *lst, t_env *env, int size, t_user *start)
{
	int		status;
	void	*ptr;
	int		old_fd[2];

	ptr = lst;
	(void)size;
	while (lst)
	{
		exec_fork(lst, env, old_fd, start);
		old_fd[0] = lst->fd[0];
		old_fd[1] = lst->fd[1];
		lst = lst->next;
	}
	lst = ptr;
	while (lst)
	{
		close(lst->fd[0]);
		lst = lst->next;
	}
	lst = ptr;
	while (lst)
	{
		waitpid(lst->pid, &status, 8 | WUNTRACED); // WCONTINUED Devient 8 sur mon OS
		old_fd[0] = lst->fd[0];
		old_fd[1] = lst->fd[1];
		lst = lst->next;
	}
	lst = ptr;
	while (lst)
	{
		if (cmd_valididy(lst->builtin) == 0)
			error_output_token(-6, lst->builtin);
		lst = lst->next;
	}
	return (1);
}