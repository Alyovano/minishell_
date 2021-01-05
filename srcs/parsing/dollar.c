/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 10:45:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 10:49:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_strn_dup(const char *s1, int len)
{
	size_t	longueur;
	char	*tab;

	longueur = len;
	if (!(tab = malloc(sizeof(char) * longueur)))
		malloc_error();
	ft_strlcpy(tab, s1, longueur);
	return (tab);
}

int			simple_quote_get_len_and_validity(t_user *start,
								t_quote *quote, int i, int j)
{
	quote->len = 0;
	while (start->user_cmd_tab[i][j]
	&& (quote->squote % 2 != 0 || quote->dquote % 2 != 0))
	{
		if (start->user_cmd_tab[i][j] == '"')
		{
			if (get_backslash(start->user_cmd_tab[i], j) == 0
			&& quote->squote % 2 == 0)
				quote->dquote++;
		}
		else if (start->user_cmd_tab[i][j] == '\'')
		{
			if (quote->squote % 2 == 0 && quote->dquote % 2 == 0)
			{
				if (get_backslash(start->user_cmd_tab[i], j) == 0)
					quote->squote++;
			}
			else if (quote->squote % 1 == 0 && quote->dquote % 2 == 0)
				quote->squote++;
		}
		j++;
		quote->len++;
	}
	return (quote->len - 1);
}

/*
**  ce token (quote->dollar_quote) permet de savoir
**  si on est pas deja dans une doucle quote
**	pcq si c'est le cas meme entre simple quote, il faudrait afficher
**	la var d'envi --- exemple de piege possible
**	input> " '$USER' "
**	output> "'alyovano'"
*/

int			free_dol(t_dollar *dol, char *one, char *two)
{
	if (dol->var_content)
		free(dol->var_content);
	if (dol->before_str)
		free(dol->before_str);
	if (dol->after_str)
		free(dol->after_str);
	if (one)
		free(one);
	if (two)
		free(two);
	return (0);
}

int			check_simple_quote(t_user *start, t_quote *quote, int j, int i)
{
	if (start->user_cmd_tab[i][j] == '\''
	&& (get_backslash(start->user_cmd_tab[i], j) == 0)
	&& quote->dollar_quote % 2 == 0)
	{
		quote->squote = 1;
		simple_quote_get_len_and_validity(start, quote, i, j + 1);
		j += quote->len;
		quote->squote = 0;
	}
	if (start->user_cmd_tab[i][j] == '"'
	&& (get_backslash(start->user_cmd_tab[i], j) == 0))
	{
		quote->dollar_quote += 1;
	}
	return (j);
}

int			str_check(char *str_envi, char *to_catch)
{
	int i;
	int len;
	int check;

	i = 0;
	check = 0;
	len = ft_strlen(to_catch);
	while (i < len)
	{
		if (to_catch[i] == str_envi[i])
		{
			check++;
		}
		i++;
	}
	if (check == len && str_envi[i] == '=')
		return (0);
	return (1);
}

char		*check_var_in_env(char *var_name, t_env *env)
{
	int		i;
	int		token_copy;
	char	*new;

	i = 0;
	token_copy = 0;
	while (env->tab[i])
	{
		if (str_check(env->tab[i], var_name) == 0)
		{
			if (env->tab[i])
				token_copy = 1;
			break ;
		}
		i++;
	}
	if (token_copy == 1)
		new = ft_substr(env->tab[i], ft_strlen(var_name) + 1, ft_strlen(env->tab[i]));
	else
		new = ft_strdup("");
	return (new);
}

/*
**ici start->user_cmd_tab[i][j] == '$' au depart
**k represente la len du nom de la variable d'envi
**Je suis pas sur dans la while pour : start->user_cmd_tab[i][j] != '='
*/

// ne pas oublier de placer les free ici
int			dollar_var_name(t_user *start, int i, int j, t_dollar *dol, t_env *env)
{
	int tmp;
	int k;
	char *one;
	char *two;

	j += 1;
	tmp = j;
	k = 0;
	while (start->user_cmd_tab[i][j + k] && start->user_cmd_tab[i][j + k] != ' '
	&& start->user_cmd_tab[i][j + k] != '\'' && start->user_cmd_tab[i][j + k] != '"'
	&& start->user_cmd_tab[i][j + k] != '=' && start->user_cmd_tab[i][j + k] != '.')
		k++;
	dol->var_name = ft_substr(start->user_cmd_tab[i], tmp, k);
	dol->var_content = check_var_in_env(dol->var_name, env);
	dol->before_str = ft_substr(start->user_cmd_tab[i], 0, j - 1);
	dol->after_str = ft_substr(start->user_cmd_tab[i], j + k, ft_strlen(start->user_cmd_tab[i]));
	one = ft_strjoin(dol->before_str, dol->var_content);
	two = ft_strjoin(one, dol->after_str);
	free(start->user_cmd_tab[i]);
	start->user_cmd_tab[i] = ft_strdup(two);
	tmp = ft_strlen(one);
	//free_dol(dol, one, two);
	// if (dol->var_name != NULL)
	// 	free(dol->var_name);
	return (tmp);
}

/*
** remplace $? par la valeur de retour precedente
** Retourne la taille de la valeur de $?
*/

int			previous_return_value(t_user *start, int i, int j, t_dollar *dol)
{
	int int_size;
	char *value;
	char *one;
	char *two;

	int_size = 0;
	value = ft_itoa(errno);
	j += 1;
	dol->before_str = ft_substr(start->user_cmd_tab[i], 0, j - 1);
	dol->after_str = ft_substr(start->user_cmd_tab[i], j + 1, ft_strlen(start->user_cmd_tab[i]));
	one = ft_strjoin(dol->before_str, value);
	two = ft_strjoin(one, dol->after_str);
	free(start->user_cmd_tab[i]);
	start->user_cmd_tab[i] = ft_strdup(two);
	int_size = ft_strlen(one);
	return (int_size);
}

/*
** j = check_simple_quote(start, quote, j, i);// jump sur la char apres la squote
*/

int				check_dollar_or_not_dollar(t_user *start,
						t_quote *quote, int i, t_dollar *dol, t_env *env)
{
	int j;
	int token;

	j = 0;
	quote->dollar_quote = 0;
	while (start->user_cmd_tab[i][j])
	{
		token = 0;
		j = check_simple_quote(start, quote, j, i);
		if (start->user_cmd_tab[i][j] == '$' &&
					(get_backslash(start->user_cmd_tab[i], j) == 0)
					&& (start->user_cmd_tab[i][j + 1])
					&& (start->user_cmd_tab[i][j + 1] != ' ')
					&& (start->user_cmd_tab[i][j + 1] != '"'))
		{
			if (start->user_cmd_tab[i][j + 1] && (start->user_cmd_tab[i][j + 1] == '?'))
			{
				token = 1;
				j = previous_return_value(start, i, j, dol);
			}
			else
				j = dollar_var_name(start, i, j, dol, env);
		}
		if (token != 1)
			j++;
	}
	return (0);
}

/*
** PLACER LES FREE
** free(dol) avant le return
*/

int				add_environnement_var(t_user *start, t_quote *quote, t_env *env)
{
	int			i;
	t_dollar	*dol;

	dol = malloc(sizeof(dol));
	if (!dol)
		malloc_error();
	i = 0;
	dol->start_cut = 0;
	while (start->user_cmd_tab[i])
	{
		check_dollar_or_not_dollar(start, quote, i, dol, env);
		i++;
	}
	free(dol);
	return (0);
}
