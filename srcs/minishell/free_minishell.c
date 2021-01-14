#include "../includes/minishell.h"

void		free_all(t_user *start)
{
	void	*tmp;
	t_list	*lst;

	tmp = start->line;

	//free_double_tab(env->tab); // CE TABLEAU EST MAUDIT
	//free_double_tab(start->user_cmd_tab);
	while (start->line)
	{
		lst = start->line->content;
		while (lst)
		{
			free(lst->content);
			free_double_tab(lst->in_types);
			free_double_tab(lst->in);
			free_double_tab(lst->out_types);
			free_double_tab(lst->out);
			free_double_tab(lst->tab_cmd);
			lst = lst->next;
		}
		start->line = start->line->next;
	}
	start->line = tmp;
	free(start->line);
	free(lst);
	//free(start->user_input);
	//free(env);
}