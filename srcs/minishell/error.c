/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 08:42:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 16:11:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		malloc_error(void)
{
	strerror(errno);
	exit(EXIT_FAILURE);
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
		g_errno = 2;
	}
	else if (error == -4)
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « newline »\n", STDERR_FILENO);
	else if (error == -5)
	{
		ft_putstr_fd("Minishell cannot do that: No multilines\n", STDERR_FILENO);
		g_errno = 444; // arbitraire, ca existe pas dans bash cette 
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
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « ", STDERR_FILENO);
		ft_putchar_fd(c, STDERR_FILENO);
		ft_putstr_fd(" »\n", STDERR_FILENO);
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
		ft_putstr_fd("Minishell cannot do that: only absolute path (ex. /bin/echo)\n", STDERR_FILENO);
		g_errno = 445; // arbitraire, ca existe pas dans bash cette 
	}
	//Ici ca va free comme jaja  --> free dans minishell avant de reprendre boucle while
}
