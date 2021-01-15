/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:24:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 10:42:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** (set_input)
** go trough lst->in file list
** open file and create if needed
** redirrect input at the end
*/

int		set_input(t_list *lst, t_fd *fds, int i)
{
	while (lst->in[i])
	{
		if (ft_strcmp(lst->in_types[i], "READ") == 0)
		{
			fds->fdin = open(lst->in[i], O_RDONLY);
			if (fds->fdin == -1)
			{
				error_output_token(-8, lst->in[i], '\0');
				return (-1);
			}
		}
		else if (ft_strcmp(lst->in_types[i], "READ_CREATE") == 0)
			fds->fdin = open(lst->in[i], O_RDONLY | O_CREAT | O_TRUNC, 0664);
		if (lst->in[i + 1] != NULL)
			close(fds->fdin);
		i++;
	}
	if (dup2(fds->fdin, 0) == -1)
	{
		error_output_token(-11, NULL, '\0');
		return (-1);
	}
	close(fds->fdin);
	return (0);
}

/*
** (set_output)
** go trough lst->out file list
** open file and create if needed
** redirrect output at the end
*/

int		set_output(t_list *lst, t_fd *fds, int i)
{
	while (lst->out[i])
	{
		if (ft_strcmp(lst->out_types[i], "WRITE") == 0)
			fds->fdout = open(lst->out[i], \
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (ft_strcmp(lst->out_types[i], "APPEND") == 0)
			fds->fdout = open(lst->out[i], \
					O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (lst->out[i + 1] != NULL)
			close(fds->fdout);
		i++;
	}
	if (dup2(fds->fdout, 1) == -1)
	{
		error_output_token(-11, NULL, '\0');
		return (-1);
	}
	close(fds->fdout);
	return (0);
}

/*
** (in_out_setup)
** save in / out before
** if in/out file(s) --> setup in set_output / set_input
*/

int		in_out_setup(t_fd *fds, t_list *lst)
{
	int		i;

	i = 0;
	fds->tmpin = dup(0);
	fds->tmpout = dup(1);
	if (fds->tmpin == -1 || fds->tmpout == -1)
	{
		error_output_token(-11, NULL, '\0');
		return (-1);
	}
	if (lst->in[0] == NULL || lst->out[0] == NULL)
		pipe(lst->fd);
	if (lst->in[0] != NULL)
		if (set_input(lst, fds, i) == -1)
			return (-1);
	if (lst->out[0] != NULL)
		if (set_output(lst, fds, i) == -1)
			return (-1);
	return (0);
}
