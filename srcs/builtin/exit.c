#include "../includes/minishell.h"

int			ft_exit(t_env *env, t_list *lst, t_user *start)
{
	(void)env;
	(void)lst;
	(void)start;
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}