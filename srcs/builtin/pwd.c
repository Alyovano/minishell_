#include "../includes/minishell.h"

int         ft_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	ret = ft_strjoin(ret, "\n");
	printf("%s\n", ret);
    return (1);
}


int main()
{
    ft_pwd();
}