/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 14:13:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function to set gerrno
** variable that contains $? value
*/

void		set_gerrno(t_list *lst, t_env *env)
{
	int			error;
	struct stat	test;
	char		**paths;

	if (find_char(lst->tab_cmd[0], '/') == 1)
	{
		if (stat(lst->tab_cmd[0], &test) == -1)
		{
			g_errno = 127;
		}
	}
	else if (cmd_valididy(lst->tab_cmd[0], env) == 0)
	{
		error = errno;
		paths = get_path(env->tab, lst->tab_cmd[0]);
		if (error == 13 || paths == NULL)
			g_errno = 1;
		else
			g_errno = 127;
		free_paths(paths);
	}
	else
		g_errno = 0;
}

void		error_output_token2(int error)
{
	if (error == -1)
	{
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « ; »\n"
															, STDERR_FILENO);
		g_errno = 2;
	}
	else if (error == -2)
	{
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « > »\n"
															, STDERR_FILENO);
		g_errno = 2;
	}
	else if (error == -4)
		ft_putstr_fd(
			"bash: erreur de syntaxe près du symbole inattendu « newline »\n"
			, STDERR_FILENO);
	else if (error == -5)
	{
		ft_putstr_fd("Minishell cannot do that: No multilines\n"
															, STDERR_FILENO);
		g_errno = 444;
	}
}

void		error_output_token3(int error, char *str, char c)
{
	if (error == -6)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": commande introuvable\n", STDERR_FILENO);
		g_errno = 127;
	}
	else if (error == -7)
	{
		if (str == NULL)
		{
			ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « "
															, STDERR_FILENO);
			ft_putchar_fd(c, STDERR_FILENO);
			ft_putstr_fd(" »\n", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « "
															, STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(" »\n", STDERR_FILENO);
		}
		g_errno = 2;
	}
}

void		error_output_token4(int error, char *str)
{
	if (error == -8)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", STDERR_FILENO);
		g_errno = 1;
	}
	else if (error == -9)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission non accordée\n", STDERR_FILENO);
		g_errno = 1;
	}
	else if (error == -10)
	{
		ft_putstr_fd("Minishell: fork error\n", STDERR_FILENO);
		g_errno = 444;
	}
}

/*
** Modification de la fonction error_output_token pour permettre l'envoi de
** chaine de caractères pour imprimer une erreur
*/

void		error_output_token(int error, char *str, char c)
{
	error_output_token2(error);
	error_output_token3(error, str, c);
	error_output_token4(error, str);
	if (error == -11)
	{
		ft_putstr_fd("Minishell: dup error\n", STDERR_FILENO);
		g_errno = 444;
	}
}
