#include "../includes/minishell.h"

int		exec_redirrect(t_list *lst, t_env *env, int old_fd[2], int size)
{	
	t_fd	fds;
	int 	i;

	i = 0;
	//save in / out
	fds.tmpin = dup(0);
	fds.tmpout = dup(1);
	//setup pipe for no file use
	if (lst->in[0] == NULL || lst->out[0] == NULL)
		pipe(lst->fd);
	//setup input with file
	if (lst->in[0] != NULL)
	{
		while (lst->in[i]) //input from redirrections
		{
			if (ft_strcmp(lst->in_types[i], "READ") == 0)
			{
				ft_printf("READ\n");
				fds.fdin = open(lst->in[i], O_RDONLY);
				if (fds.fdin == -1)
				{
					error_output_token(-8, lst->in[i], '\0');
					return (-1);
				}
			}
			else if (ft_strcmp(lst->in_types[i], "READ_CREATE") == 0)
			{
				ft_printf("READ_CREATE\n");
				fds.fdin = open(lst->in[i], O_RDONLY | O_CREAT | O_TRUNC, 0664);
			}
			if (lst->in[i + 1] != NULL)
				close(fds.fdin);
			i++;
		}
		//redirret input
		dup2(fds.fdin, 0);
		close(fds.fdin);
	}
	
	//setup output with file
	i = 0;
	if (lst->out[0] != NULL)
	{
		while (lst->out[i]) //input from redirrections
		{
			if (ft_strcmp(lst->out_types[i], "WRITE") == 0)
			{
				ft_printf("Write\n");
				fds.fdout = open(lst->out[i], O_WRONLY | O_CREAT | O_TRUNC, 0664);				
			}
			else if (ft_strcmp(lst->out_types[i], "APPEND") == 0)
			{
				ft_printf("APPEND\n");
				fds.fdout = open(lst->out[i], O_WRONLY | O_CREAT | O_APPEND, 0664);				
			}
			if (lst->out[i + 1] != NULL)
				close(fds.fdout);
			i++;
		}
		//redirrect output
		dup2(fds.fdout, 1);
		close(fds.fdout);
	}
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
		
		//fork
		//lst->pid = fork();
		
		dispatch_cmd(lst, env);
		perror("EXECVP");
		exit(1);
	}
	if (lst->out[0] == NULL || lst->in[0] == NULL)
		close(lst->fd[1]);
	dup2(fds.tmpin, 0);
	dup2(fds.tmpout, 1);
	close(fds.tmpin);
	close(fds.tmpout);
	

	/*
	while (lst)
	{
		ft_printf("BUILIN: %s\n", lst->builtin);
		lst = lst->next;
	}*/
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
		waitpid(lst->pid, &status, 8 | WUNTRACED);
		lst = lst->next;
	}
	return (0);
}