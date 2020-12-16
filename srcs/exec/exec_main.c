#include "../includes/minishell.h"

/*
** (set_input)
** go trough lst->in file list
** open file and create if needed
** redirrect input at the end
*/

int		set_input(t_list *lst, t_fd *fds, int i)
{
	while (lst->in[i])
	{
		if (ft_strcmp(lst->in_types[i], "READ") == 0)
		{
			fds->fdin = open(lst->in[i], O_RDONLY);
			if (fds->fdin == -1)
			{
				error_output_token(-8, lst->in[i], '\0');
				return (-1);
			}
		}
		else if (ft_strcmp(lst->in_types[i], "READ_CREATE") == 0)
			fds->fdin = open(lst->in[i], O_RDONLY | O_CREAT | O_TRUNC, 0664);
		if (lst->in[i + 1] != NULL)
			close(fds->fdin);
		i++;
	}
	dup2(fds->fdin, 0);
	close(fds->fdin);
	return (0);
}

/*
** (set_output)
** go trough lst->out file list
** open file and create if needed
** redirrect output at the end
*/

void		set_output(t_list *lst, t_fd *fds, int i)
{
	while (lst->out[i])
	{
		if (ft_strcmp(lst->out_types[i], "WRITE") == 0)
			fds->fdout = open(lst->out[i], O_WRONLY | O_CREAT | O_TRUNC, 0664);				
		else if (ft_strcmp(lst->out_types[i], "APPEND") == 0)
			fds->fdout = open(lst->out[i], O_WRONLY | O_CREAT | O_APPEND, 0664);				
		if (lst->out[i + 1] != NULL)
			close(fds->fdout);
		i++;
	}
	dup2(fds->fdout, 1);
	close(fds->fdout);
}

/*
** (in_out_setup)
** save in / out before
** if in/out file(s) --> setup in set_output / set_input
*/

int		in_out_setup(t_fd *fds, t_list *lst)
{
	int 	i;

	i = 0;
	fds->tmpin = dup(0);
	fds->tmpout = dup(1);
	if (lst->in[0] == NULL || lst->out[0] == NULL)
		pipe(lst->fd);
	if (lst->in[0] != NULL)
		if (set_input(lst, fds, i) == -1)
			return (-1);
	if (lst->out[0] != NULL)
		set_output(lst, fds, i);
	return (0);
}

int		is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || \
		ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || \
		ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 || \
		ft_strcmp(cmd, "env") == 0 || \
		ft_strcmp(cmd, "exit") == 0 || \
		ft_strcmp(cmd, "$?") == 0)
		return(1);
	return (0);
}

int		exec_redirrect(t_list *lst, t_env *env, int old_fd[2], int size)
{	
	t_fd	fds;

	if (in_out_setup(&fds, lst) == -1)
		return (-1);
		
	if (size == 1 && (ft_strcmp("export", lst->builtin) == 0 || ft_strcmp("cd", lst->builtin) == 0 \
					|| ft_strcmp("unset", lst->builtin) == 0))
	{
		//exception solo file no fork
		dispatch_cmd(lst, env);
	}
	else
	{
		lst->pid = fork();
		if (lst->pid == 0)
		{
			if (size != 1)
			{
				//pipe setup for cmd with no file
				if (lst->stdout_fd && lst->out[0] == NULL)
				{
					dup2(lst->fd[1], STDOUT_FILENO);
					close(lst->fd[0]);
				}
				if (lst->stdin_fd && lst->in[0] == NULL)
				{
					dup2(old_fd[0], STDIN_FILENO);
					close(old_fd[1]);
				}
			}
			dispatch_cmd(lst, env);
			if (cmd_valididy(lst->builtin, env) == 0)
				error_output_token(-6, lst->builtin, '\0');
			exit(EXIT_FAILURE);
		}
	}
	if (lst->out[0] == NULL || lst->in[0] == NULL)
		close(lst->fd[1]);
	dup2(fds.tmpin, 0);
	dup2(fds.tmpout, 1);
	close(fds.tmpin);
	close(fds.tmpout);
	return (1);
}

int		exec_main(t_list *lst, t_env *env)
{
	int		status;
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
	return (0);
}