#include "../includes/minishell.h"

int		redirrect_error(char *elem)
{
	int i;

	i = ft_strlen(elem) - 1;
	while (elem[i] && (elem[i] == ' ' || elem[i] == '<' || elem[i] == '>'))
	{
		if ((elem[i] == '>' || elem[i] == '<') && get_backslash(elem, i) == 0)
		{
			error_output_token(-7, NULL, elem[i]);
			return (-1);
		}
		i--;
	}
	return (0);
}

int		check_redirrect(char *str, int i)
{
	if (str[i] == ' ')
		i++;
	if (str[i] == '>' || str[i] == '<')
	{
		error_output_token(-7, NULL, str[i]);
		return (-1);
	}
	return (0);
}