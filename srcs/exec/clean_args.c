#include "../includes/minishell.h"

/*
** Function to clean spaces at end of line
** send &lst->argu to remove spaces and set new value
*/

void		clean_end_spaces(char **str)
{
	int		i;
	char	*tmp;
	
	i = ft_strlen(*str) - 1;
	while ((*str)[i] && (*str)[i] == ' ')
		i--;
	tmp = ft_str_n_dup(*str, i + 1);
	free(*str);
	*str = tmp;
}

/*
** Function to clean args
** We can add clean another clean function to clean \' \" and remove quotes before printing
*/

void		clean_args(t_list *lst)
{
	while (lst)
	{
		clean_end_spaces(&lst->argu);
		lst = lst->next;
	}
}