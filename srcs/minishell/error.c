/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 16:22:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		malloc_error(void)
{
	strerror(errno);
	exit(EXIT_FAILURE);
}

void		print_trio_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
}

/*
** Error output from CD builtin
*/

void		var_name_error(int err, char *str)
{
	g_errno = err;
	print_trio_error("minishell: export: « ", str, " » : identifiant non valable\n");
}

int			dirr_error(char *path)
{
	g_errno = 1;
	print_trio_error("bash: cd: ", path, ": ");
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (0);
}

void		unset_error(char *str)
{
	print_trio_error("minishell: unset: « ", str, "» : identifiant non valable\n");
}

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

/*
** Modification de la fonction error_output_token pour permettre l'envoi de
** chaine de caractères pour imprimer une erreur
*/

void		error_output_token(int error, char *str, char c)
{
	if (error == -1)
	{
		ft_putstr_fd("minishell: erreur de syntaxe près du symbole inattendu « ; »\n", STDERR_FILENO);
		g_errno = 2;
	}
	else if (error == -2)
	{
		ft_putstr_fd("minishell: erreur de syntaxe près du symbole inattendu « > »\n", STDERR_FILENO);
		g_errno = 2;
	}
	else if (error == -3)
	{
		ft_putstr_fd("Minishell cannot do that: No multilines : « < »\n", STDERR_FILENO);
		g_errno = 444;
	}
	else if (error == -4)
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « newline »\n", STDERR_FILENO);
	else if (error == -5)
	{
		ft_putstr_fd("Minishell cannot do that: No multilines\n", STDERR_FILENO);
		g_errno = 444;
	}
	else if (error == -6)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": commande introuvable\n", STDERR_FILENO);
		g_errno = 127;
	}
	else if (error == -7)
	{
		if (str == NULL)
		{
			ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « ", STDERR_FILENO);
			ft_putchar_fd(c, STDERR_FILENO);
			ft_putstr_fd(" »\n", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(" »\n", STDERR_FILENO);
		}
		g_errno = 2;
	}
	else if (error == -8)
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
	else if (error == -11)
	{
		ft_putstr_fd("Minishell: dup error\n", STDERR_FILENO);
		g_errno = 444;
	}
	//Ici ca va free comme jaja  --> free dans minishell avant de reprendre boucle while
}
