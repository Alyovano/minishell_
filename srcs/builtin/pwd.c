#include "../includes/minishell.h"

int         ft_pwd(void)
{
    size_t size;
    size = 90;
    char    buf[9000];
    getcwd(buf, size);
    printf("%s\n", buf);
    printf("%ld\n", size);
    return (0);
}


int main()
{
    ft_pwd();
}