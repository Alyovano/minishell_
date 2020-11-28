#include "../includes/minishell.h"

int         ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	ft_printf("%s\n", tmp);
	//free(tmp); ? 
    return (0);
}