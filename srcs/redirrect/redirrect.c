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

char	*get_file(char *str, int i, t_quote *quote)
{
	char	*tmp;
	int		j;

	j = 0;
	quote->token_in_dquote = -1;
	quote->token_in_simple_quote = -1;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	if (!tmp)
		malloc_error();
	while (str[i])
	{
		//ft_printf("get_file %c\n", str[i]);
		if (quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1 \
			&& (str[i] == '\'' ||  str[i] == '"') && get_backslash(str, i) == 0)
		{
			//on rentre dans une quote
			if (str[i] == '\'')
				quote->token_in_simple_quote *= -1;
			else
				quote->token_in_dquote *= -1;
			i++;
		}
		if (quote->token_in_dquote == 1 && str[i] == '"' && get_backslash(str, i) == 0)
		{
			//end quote
			quote->token_in_dquote *= -1;
			i++;
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
			{
				//return value of file name
				tmp[++j] = '\0';
				return (tmp);
			}
		}
		else if (quote->token_in_simple_quote == 1 && str[i] == '\'' && get_backslash(str, i) == 0)
		{
			//end quote
			quote->token_in_simple_quote *= -1;
			i++;
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
			{
				//return value of file name
				tmp[++j] = '\0';
				return (tmp);
			}
		}
		//ft_printf("get_file: %d %d %c\n", quote->token_in_simple_quote, quote->token_in_dquote, str[i]);
		if (quote->token_in_dquote == -1 && quote->token_in_simple_quote == -1 \
			&& str[i] == ' ')
		{
			//fin de ligne ou espace return
			tmp[++j] = '\0';
			return (tmp);
		}
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*get_file_path(char *str, int i, t_quote *quote)
{
	char	*file_name;
	char	*file_path;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		malloc_error();
	file_name = get_file(str, i , quote);
	if (strcmp(pwd, "/") != 0)
	{
		tmp = ft_strdup(file_name);
		file_name = ft_strjoin("/", tmp);
		free(tmp);
	}
	file_path = ft_strjoin(pwd, file_name);
	free(pwd);
	free(file_name);
	return (file_path);
}

//fd = open(file_path, O_RDONLY | O_CREAT, 0664);
void	write_redirrect(char *str, int i, t_list *lst, char *type)
{
	char	*file_path;
	char	**tmp;
	t_quote	quote;

	if (str[i] == ' ')
		i++;
	file_path = get_file_path(str, i, &quote);
	tmp = add_str_to_tab(lst->out, file_path);
	free_double_tab(lst->out);
	lst->out = copy_double_tab(tmp);
	free_double_tab(tmp);
	free(file_path);
	tmp = add_str_to_tab(lst->out_types, type);
	free_double_tab(lst->out_types);
	lst->out_types = copy_double_tab(tmp);
	free_double_tab(tmp);
}

void	read_redirrect(char *str, int i, t_list *lst, char *type)
{
	char	*file_path;
	char	**tmp;
	t_quote	quote;

	if (str[i] == ' ')
		i++;
	file_path = get_file_path(str, i, &quote);
	tmp = add_str_to_tab(lst->in, file_path);
	free_double_tab(lst->in);
	lst->in = copy_double_tab(tmp);
	free_double_tab(tmp);
	free(file_path);
	tmp = add_str_to_tab(lst->in_types, type);
	free_double_tab(lst->in_types);
	lst->in_types = copy_double_tab(tmp);
	free_double_tab(tmp);
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
	//ft_printf("Elem actuel: |%s| |%c| %d\n", tmp, tmp[ft_strlen(tmp) - 1], ft_strlen(tmp));
	if (redirrect_error(tmp) == -1)
		return (-1); 
	while (tmp[i])
	{
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
