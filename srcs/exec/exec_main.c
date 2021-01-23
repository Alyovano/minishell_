/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:53:07 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 11:08:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		exec_close(t_list *lst, t_fd *fds)
{
	if (lst->out[0] == NULL || lst->in[0] == NULL)
		close(lst->fd[1]);
	if (dup2(fds->tmpin, 0) == -1 || dup2(fds->tmpout, 1) == -1)
	{
		error_output_token(-11, NULL, '\0');
		return (-1);
	}
	close(fds->tmpin);
	close(fds->tmpout);
	return (0);
}

int		exec_redirrect(t_list *lst, t_env *env, int old_fd[2], int size)
{
	t_fd	fds;

	if (in_out_setup(&fds, lst) == -1)
		return (-1);
	if (size == 1 && (ft_strcmp("export", lst->tab_cmd[0]) == 0 || \
							ft_strcmp("cd", lst->tab_cmd[0]) == 0 || \
							ft_strcmp("unset", lst->tab_cmd[0]) == 0))
		dispatch_cmd(lst, env);
	else
	{
		lst->pid = fork();
		if (lst->pid == -1)
		{
			error_output_token(-10, NULL, '\0');
			return (-1);
		}
		if (lst->pid == 0)
			if (exec_type(size, old_fd, env, lst) == -1)
				return (-1);
	}
	if (exec_close(lst, &fds) == -1)
		return (-1);
	return (1);
}

void	exec_main2(void *ptr, t_list *lst)
{
	int		status;

	lst = ptr;
	while (lst)
	{
		close(lst->fd[0]);
		lst = lst->next;
	}
	lst = ptr;
	while (lst)
	{
		if (lst->pid != -1)
		{
			if (g_reg == -1)
			{
				while (lst)
				{
					kill(lst->pid, SIGKILL);
					lst = lst->next;
				}
				return ;
			}
			g_reg = 1;
			waitpid(lst->pid, &status, 8 | WUNTRACED);
		}
		if (lst->next == NULL && g_errno != 127)
			g_errno = status / 256;
		lst = lst->next;
	}
}

int		exec_main(t_list *lst, t_env *env)
{
	void	*ptr;
	int		old_fd[2];
	int		size;

	ptr = lst;
	size = ft_lstsize(lst);
	while (lst)
	{
		set_gerrno(lst, env);
		lst = lst->next;
	}
	lst = ptr;
	while (lst)
	{
		if (exec_redirrect(lst, env, old_fd, size) == -1)
			return (-1);
		old_fd[0] = lst->fd[0];
		old_fd[1] = lst->fd[1];
		lst = lst->next;
	}
	exec_main2(ptr, lst);
	return (0);
}
