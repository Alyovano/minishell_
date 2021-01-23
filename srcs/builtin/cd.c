/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:06:18 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 13:26:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		unkillable_var(t_env *env, char *path)
{
	char		**new;
	int			i;

	i = double_tab_size(env->tab);
	new = malloc(sizeof(char *) * (i + 2));
	if (new == NULL)
		malloc_error();
	i = 0;
	while (env->tab[i])
	{
		new[i] = ft_strdup(env->tab[i]);
		i++;
	}
	new[i] = ft_strdup(path);
	new[i + 1] = NULL;
	free_double_tab(env->tab);
	env->tab = copy_double_tab(new);
	free_double_tab(new);
}

int			change_pwd(t_env *env)
{
	int		j;
	int		token;
	char	*tmp;
	char	*tmp_s;

	j = 0;
	token = 0;
	tmp = getcwd(NULL, 0);
	tmp_s = ft_strjoin("PWD=", tmp);
	while (env->tab[j])
	{
		if (catch_env_varr("PWD", env->tab[j]) == 0)
		{
			free(env->tab[j]);
			env->tab[j] = ft_strdup(tmp_s);
			token = 1;
		}
		j++;
	}
	if (token != 1)
		unkillable_var(env, tmp_s);
	free(tmp);
	free(tmp_s);
	return (0);
}

int			change_old_pwd(char *oldpwd, t_env *env)
{
	int		j;
	int		token;
	char	*tmp;
	char	*tmp_s;

	j = 0;
	token = 0;
	tmp = ft_strdup(oldpwd);
	tmp_s = ft_strjoin("OLDPWD=", tmp);
	while (env->tab[j])
	{
		if (catch_env_varr("OLDPWD", env->tab[j]) == 0)
		{
			free(env->tab[j]);
			env->tab[j] = ft_strdup(tmp_s);
			token = 1;
		}
		j++;
	}
	if (token != 1)
		unkillable_var(env, tmp_s);
	free(tmp);
	free(tmp_s);
	return (0);
}

int			go_home(char *tmp, char *var_name, t_env *env)
{
	char *var_content;

	var_content = check_var_in_env(var_name, env);
	chdir(var_content);
	free(var_content);
	change_old_pwd(tmp, env);
	change_pwd(env);
	return (0);
}

int			ft_cd(t_env *env, t_list *lst)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	if (double_tab_size(lst->tab_cmd) == 1)
	{
		go_home(tmp, "HOME", env);
		free(tmp);
		return (0);
	}
	if (chdir(lst->tab_cmd[1]) == 0)
	{
		change_old_pwd(tmp, env);
		change_pwd(env);
	}
	else if (lst->tab_cmd[1][0] != '\0')
		dirr_error(lst->tab_cmd[1]);
	free(tmp);
	return (0);
}
