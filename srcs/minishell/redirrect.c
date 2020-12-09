#include "../includes/minishell.h"

int		is_redirrect(t_list *lst, t_quote *quote)
{
	char	*tmp;
	int		i;
	
	i = 0;
	tmp = ft_strdup(lst->content);
	quote->token_in_dquote = -1;
	quote->token_in_simple_quote = -1;
	if (!tmp)
	{
		perror("Malloc Failure\n");
		exit (EXIT_FAILURE);
	} 
	// ici j'ai fais une fonction malloc_error()
	// comme ca tu economise 3 lignes
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

int		redirrect_error(char *elem)
{
	int i;

	i = ft_strlen(elem) - 1;
	while (elem[i] && (elem[i] == ' ' || elem[i] == '<' || elem[i] == '>'))
	{
		if (elem[i] == '>' || elem[i] == '<')
		{
			error_output_token(-7, NULL, elem[i]);
			return (-1);
		}
		i--;
	}
	return (0);
}

int		get_redirrect(t_list *lst, t_quote *quote)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(lst->content);
	quote->token_in_dquote = -1;
	quote->token_in_simple_quote = -1;
	//ft_printf("Elem actuel: |%s| |%c| %d\n", tmp, tmp[ft_strlen(tmp) - 1], ft_strlen(tmp));
	if (redirrect_error(tmp) == -1)
		return (-1); 
	while (tmp[i])
	{
		if (tmp[i] == '\'' && get_backslash(tmp, i) == 0)
			quote->token_in_simple_quote *= -1;
		else if (tmp[i] == '"' && get_backslash(tmp, i) == 0)
			quote->token_in_dquote *= -1;
		else if ((tmp[i] == '>' || tmp[i] == '<') && get_backslash(tmp, i) == 0 
			&& quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1)
			ft_printf("Redirrect found !\n");
		i++;
	}
	free(tmp);
	return (1);
}
