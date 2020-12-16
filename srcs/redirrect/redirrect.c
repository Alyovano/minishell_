#include "../includes/minishell.h"

int		is_redirrect(t_list *lst, t_quote *quote)
{
	char	*tmp;
	int		i;
	
	i = 0;
	tmp = ft_strdup(lst->content);
	quote->token_in_dquote = -1;
	quote->token_in_simple_quote = -1;
	while (tmp[i])
	{
		if (tmp[i] == '\'' && get_backslash(tmp, i) == 0)
			quote->token_in_simple_quote *= -1;
		else if (tmp[i] == '"' && get_backslash(tmp, i) == 0)
			quote->token_in_dquote *= -1;
		else if ((tmp[i] == '>' || tmp[i] == '<') && get_backslash(tmp, i) == 0 
			&& quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1)
			return (1);
		i++;
	}
	free(tmp);
	return (0);
}

void	next_quote(char *str, int *i)
{
	if (str[*i] == '\'' && get_backslash(str, *i) == 0)
		while (str[*i] && str[*i] != '\'' && get_backslash(str, *i) == 0)
			(*i)++;
	else if (str[*i] == '"' && get_backslash(str, *i) == 0)
		while (str[*i] && str[*i] != '"' && get_backslash(str, *i) == 0)
			(*i)++;
}

int		get_redirrect(t_list *lst, t_quote *quote)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(lst->content);
	quote->token_in_dquote = -1;
	quote->token_in_simple_quote = -1;
	if (redirrect_error(tmp) == -1)
		return (-1); 
	while (tmp[i])
	{
		int test = 0; printf("%d\n", test++);
		if ((tmp[i] == '\'' || tmp[i] == '"') && get_backslash(tmp, i) == 0)
			next_quote(tmp, &i);
		else if ((tmp[i] == '>' || tmp[i] == '<') && get_backslash(tmp, i) == 0)
		{
			//algo redirrections
			if (tmp[i] == '>' && tmp[i + 1] == '>')
			{
				if (check_redirrect(tmp, i + 2) == -1)
					return (-1);
				write_redirrect(tmp, i + 2, lst, "APPEND");
				i++;
			}
			else if (tmp[i] == '<' && tmp[i + 1] == '>')
			{
				if (check_redirrect(tmp, i + 2) == -1)
					return (-1);
				read_redirrect(tmp, i + 2, lst, "READ_CREATE");
				i++;
			}
			else if (tmp[i] == '>')
			{
				if (check_redirrect(tmp, i + 1) == -1)
					return (-1);
				write_redirrect(tmp, i + 1, lst, "WRITE");
			}
			else if (tmp[i] == '<')
			{
				if (check_redirrect(tmp, i + 1) == -1)
					return (-1);
				read_redirrect(tmp, i + 1, lst, "READ");
			}
		}
		i++;
	}
	free(tmp);
	return (1);
}
