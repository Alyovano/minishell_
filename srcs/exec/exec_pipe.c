#include "../includes/minishell.h"

int		exec_pipe(t_list *lst, char **env, int size)
{
	pid_t	pid;
	int		fd[2];
	int		fd2[2];
	int		i;

	i = 0;
	while (lst)
	{
		if (i % 2 != 0) //if odd
			pipe(fd);
		else	//if even
			pipe(fd2);
		pid = fork();
		if (pid < 0)
		{
			//fork error
			close(fd[READ]);
			close(fd[WRITE]);
			close(fd2[READ]);
			close(fd2[WRITE]);
			return (-2);
		}
		if (pid == 0) // child process
		{
			if (i == 0)	//if first elem in lst, no stdin change
				dup2(fd2[WRITE], STDOUT_FILENO);
			else if (i == size - 1) //last cmd in lst, no stdout change
			{
				if (i % 2 != 0)	// if odd
				{
					close(fd[WRITE]);
					dup2(fd2[READ], STDIN_FILENO); //fd > fd2
				}
				else	//if even
				{
					close(fd2[WRITE]);
					dup2(fd[READ], STDIN_FILENO);	//fd2 > fd0
				}
			}
			else //cmd between first and last
			{
				if (i % 2 != 0) //if odd
				{
					dup2(fd2[READ], STDIN_FILENO);
					dup2(fd[WRITE], STDOUT_FILENO);
				}
				else  //if even
				{
					dup2(fd[READ], STDIN_FILENO);
					dup2(fd2[WRITE], STDOUT_FILENO);
				}
			}
			
			if (petite_execution(lst, env) == -1)
			{
				error_output_token(-6, lst->builtin);
				return (-1);	//cmd not found in /bin/
			}
		}

		/*
		** Parent process
		** Need to close every fd used in child process
		*/
		if (i == 0)	//if first elem in lst, no stdin change
		{
			close(fd2[WRITE]);
		}
		else if (i == size - 1) //last cmd in lst, no stdout change
		{
			if (i % 2 != 0)	// if odd
			{
				close(fd[READ]);
			}
			else	//if even
			{
				close(fd2[READ]);
			}
		}
		else //cmd between first and last
		{
			if (i % 2 != 0) //if odd
			{
				close(fd2[READ]);
				close(fd[WRITE]);
			}
			else  //if even
			{
				close(fd[READ]);
				close(fd2[WRITE]);
			}
		}
		waitpid(pid, NULL, 0);
		lst = lst->next;
		i++;
	}
	return (1);
}
