#include "../includes/minishell.h"

// int     free_all(t_user *start, t_quote *quote)
// {
//     if (start)
//     {
//         if (start->user_input)
//             free(start->user_input);
//         // i = (double_tab_size(start->user_env) + 1);
//         // free(start->user_env[0]);
//         // free(start->user_env[i]);
//         if (start->user_env)
//             free(start->user_env);
//         free(start);
//     }
//     if (quote)
//        free(quote);
// }