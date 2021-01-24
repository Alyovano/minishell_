/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 10:45:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 15:30:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_var_in_env(char *var_name, t_env *env)
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
		new = ft_substr(env->tab[i], ft_strlen(var_name) + 1, \
											ft_strlen(env->tab[i]));
	else
		new = ft_strdup("");
	return (new);
}

/*
**ici start->user_cmd_tab[i][j] == '$' au depart
**k represente la len du nom de la variable d'envi
**Je suis pas sur dans la while pour : start->user_cmd_tab[i][j] != '='
*/

int		dollar_var_name(t_list *lst, t_int_pack *p, t_dollar *dol, t_env *env)
{
	int		k;
	char	*one;
	char	*two;
	char	*tmp;

	tmp = ft_strdup(lst->tab_cmd[p->i]);
	p->j += 1;
	k = 0;
	while (tmp[p->j + k] && tmp[p->j + k] != ' ' && tmp[p->j + k] != '\''
	&& tmp[p->j + k] != '"' && tmp[p->j + k] != '=' && tmp[p->j + k] != '.'
	&& tmp[p->j + k] != '$')
		k++;
	dol->var_name = ft_substr(tmp, p->j, k);
	dol->var_content = check_var_in_env(dol->var_name, env);
	dol->before_str = ft_substr(tmp, 0, p->j - 1);
	dol->after_str = ft_substr(tmp, p->j + k, ft_strlen(tmp));
	one = ft_strjoin(dol->before_str, dol->var_content);
	two = ft_strjoin(one, dol->after_str);
	free(tmp);
	if (lst->tab_cmd[p->i])
		free(lst->tab_cmd[p->i]);
	lst->tab_cmd[p->i] = ft_strdup(two);
	p->j = ft_strlen(one) - 1;
	free_dol(dol, one, two);
	return (p->j);
}

void	dol_or_not_dol2(t_list *lst, t_int_pack *p, t_dollar *dol, t_env *env)
{
	if (lst->tab_cmd[p->i][p->j + 1] == '?')
		p->j = prev_return_value(lst, p->i, p->j, dol);
	else
		p->j = dollar_var_name(lst, p, dol, env);
}

/*
** j = check_simple_quote(start, quote, j, i);
** jump sur la char apres la squote
*/

int		ch_dollar_or_not_dollar(t_list *lst, int i, t_dollar *dol, t_env *env)
{
	char		*cmd;
	t_quote		quote;
	t_int_pack	p;

	p.j = -1;
	p.i = i;
	quote.dollar_quote = 0;
	init_quotes(&quote, -1, -1);
	while (lst->tab_cmd[p.i][++(p.j)])
	{
		cmd = ft_strdup(lst->tab_cmd[p.i]);
		if (cmd[p.j] == '\'' && get_backslash(cmd, p.j) == 0 \
										&& quote.dquote == -1)
			quote.squote *= -1;
		else if (cmd[p.j] == '"' && get_backslash(cmd, p.j) == 0)
			quote.dquote *= -1;
		if (cmd[p.j] == '$' && (get_backslash(cmd, p.j) == 0) \
			&& (cmd[p.j + 1]) && (cmd[p.j + 1] != ' ') && quote.squote == -1)
			dol_or_not_dol2(lst, &p, dol, env);
		free(cmd);
	}
	return (0);
}

int		add_environnement_var(t_list *lst, t_env *env)
{
	int			i;
	t_dollar	*dol;
	t_list		*tmp;

	dol = malloc(sizeof(t_dollar));
	if (!dol)
		malloc_error();
	i = 0;
	dol->start_cut = 0;
	tmp = lst;
	while (lst)
	{
		i = 0;
		while (lst->tab_cmd[i])
		{
			ch_dollar_or_not_dollar(lst, i, dol, env);
			i++;
		}
		lst = lst->next;
	}
	lst = tmp;
	free(dol);
	return (0);
}
