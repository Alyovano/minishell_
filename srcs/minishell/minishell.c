#include "../includes/minishell.h"



int     minishell_loop(t_user *start)
{
    char *user_Input;
    while (1)
    {
        ft_printf("minishell> ");
        get_next_line(0, &user_Input);
        free(user_Input);
    }
}

/*
** Le main aura d'autres utilites, enfin j'espere,
** Pour le moment je laisse comme ca, mais ca va bouger (je crois ?)
*/

int     main(int argc, char **argv, char **env)
{
    t_user *start;

    if (!(start = malloc(sizeof(start))))
        return (-1);
    start->user_Env = copy_double_tab(env);
    minishell_loop(start);
    //------------------------------
    int i = 0;
    while (start->user_Env[i])
    {
        ft_printf("%s\n", start->user_Env[i]);
        free(start->user_Env[i]);
        i++;
    }
    free(start->user_Env);
    free(start);
    return (0);
}