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
		execve(path, exec_arg, env);
	}
	return (-2);
}

int         execuction_temporaire(t_user *start)
{
    void *ptr;
    ptr = start->line;
    while (start->line)
    {
        petite_execution(start->line->content, start->user_env);
        debug(start->line->content);
        start->line = start->line->next;
    }
    start->line = ptr;
    return (0);
}