#include "../includes/minishell.h"

void		init_redirrect(t_list *lst)
{
	lst->out = malloc(sizeof(char *));
	if (!lst->out)
		malloc_error();
	lst->out[0] = NULL;
	lst->in = malloc(sizeof(char *));
	if (!lst->in)
		malloc_error();
	lst->in[0] = NULL;
	lst->in_types = malloc(sizeof(char *));
	if (!lst->in_types)
		malloc_error();
	lst->in_types[0] = NULL;
	lst->out_types = malloc(sizeof(char *));
	if (!lst->out_types)
		malloc_error();
	lst->out_types[0] = NULL;
}