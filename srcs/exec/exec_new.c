#include "../includes/minishell.h"

int		exec_redirrect(t_list *lst, t_env *env, int size, t_user *start)
{	
	t_fd	fds;
	int 	i;
	int		ret;
	int		status;

	(void)size;

	i = 0;
	//save in / out
	fds.tmpin = dup(0);
	fds.tmpout = dup(1);
	//setup input
	if (lst->in[0] == NULL)
		fds.fdin = dup(fds.tmpin); //default input
	else
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
	}
	//redirret input
	dup2(fds.fdin, 0);
	close(fds.fdin);
	//setup output
	i = 0;
	if (lst->out[0] == NULL)
		fds.fdout = dup(fds.tmpout); //default input
	else
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
	}
	//redirrect output
	dup2(fds.fdout, 1);
	close(fds.fdout);
	ret = fork();
	if (ret == 0)
	{
		dispatch_cmd(lst, env, start);
		perror("EXECVP");
		exit(1);
	}

	dup2(fds.tmpin, 0);
	dup2(fds.tmpout, 1);
	close(fds.tmpin);
	close(fds.tmpout);
	waitpid(ret, &status, 8 | WUNTRACED);

	/*
	while (lst)
	{
		ft_printf("BUILIN: %s\n", lst->builtin);
		lst = lst->next;
	}*/
	return (1);
}