/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:53:07 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 16:01:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		exec_redirrect(t_list *lst, t_env *env, int old_fd[2], int size)
{
	t_fd	fds;

	if (in_out_setup(&fds, lst) == -1)
		return (-1);
	if (size == 1 && (ft_strcmp("export", lst->builtin) == 0 || \
							ft_strcmp("cd", lst->builtin) == 0 || \
							ft_strcmp("unset", lst->builtin) == 0))
		dispatch_cmd(lst, env);
	else
	{
		lst->pid = fork();
		if (lst->pid == 0)
			exec_type(size, old_fd, env, lst);
	}
	if (lst->out[0] == NULL || lst->in[0] == NULL)
		close(lst->fd[1]);
	dup2(fds.tmpin, 0);
	dup2(fds.tmpout, 1);
	close(fds.tmpin);
	close(fds.tmpout);
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
		g_reg = 1;
		waitpid(lst->pid, &status, 8 | WUNTRACED);
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
		if (exec_redirrect(lst, env, old_fd, size) == -1)
			return (-1);
		old_fd[0] = lst->fd[0];
		old_fd[1] = lst->fd[1];
		lst = lst->next;
	}
	exec_main2(ptr, lst);
	return (0);
}
