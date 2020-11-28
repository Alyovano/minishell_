#include "../includes/minishell.h"

int			ft_exit(t_env *env, t_list *lst, t_user *start)
{
	(void)env;
	(void)lst;
	(void)start;
	printf("0\n");
	exit(0);
	printf("1\n");
	exit(EXIT_SUCCESS);
	printf("2\n");
	exit(EXIT_SUCCESS);
	return EXIT_SUCCESS;
}