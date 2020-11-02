#include "../includes/minishell.h"

/*
** parent_close_fd function to close fd in parent process
*/
void	parent_close_fd(int fd[2], int fd2[2], int size, int i)
{
	if (i == 0)	//if first elem in lst, no stdin change
		close(fd2[WRITE]);
	else if (i == size - 1) //last cmd in lst, no stdout change
	{
		if (i % 2 != 0)	// if odd
			close(fd[READ]);
		else	//if even
			close(fd2[READ]);
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
}

/*
** This function is called when i != 0
** ==> for every comand after the first element of the list
*/

void	child_not_first(int fd[2], int fd2[2], int size, int i)
{
	if (i == size - 1) //last cmd in lst, no stdout change
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
}

/*
** La fonction exec_pipe permet d'executer toutes les commandes séparés part un '|'
** Le résultat de chque commande est enregistrée avec pipe() et dup2()
**
** pipe() permet de créer un style de tunnel de communiquation entre differents processus
** pipe prend en paramètre un int fd[2], un fd est utilisé pour écrire et l'autre pour lire
** 
** dup2(oldfd, newfd) permet de tranformer le newfd en une copie de oldfd
** dans le cas de cette fonction, on va remplcer le fd de la sortie / entrée standard
** pour récupérer ou insérer des données de la commande précédente
**
** close() nous permet de fermer le fd. Si on ne le ferme pas, le programme va tourner en boucle
** parce que le processus parrent attent une information de l'enfant. Donc tant que c'est par fermé
** il reste en mode idle
*/
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
			else
				child_not_first(fd, fd2, size, i);
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
		parent_close_fd(fd, fd2, size, i);
		waitpid(pid, NULL, 0);
		lst = lst->next;
		i++;
	}
	return (1);
}
