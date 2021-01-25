/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:45:35 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 16:01:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		in_file(t_list *lst)
{
	int i;
	int	fd;

	i = 0;
	while (lst->in[i])
	{
		if (ft_strcmp(lst->in_types[i], "READ") == 0)
		{
			fd = open(lst->in[i], O_RDONLY);
			if (fd == -1)
			{
				error_output_token(-8, lst->in[i], '\0');
				return (-1);
			}
		}
		else if (ft_strcmp(lst->in_types[i], "READ_CREATE") == 0)
			fd = open(lst->in[i], O_RDONLY | O_CREAT | O_TRUNC, 0664);
		close(fd);
		i++;
	}
	return (0);
}

int		out_file(t_list *lst)
{
	int i;
	int fd;

	i = 0;
	while (lst->out[i])
	{
		if (ft_strcmp(lst->out_types[i], "WRITE") == 0)
			fd = open(lst->out[i], \
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (ft_strcmp(lst->out_types[i], "APPEND") == 0)
			fd = open(lst->out[i], \
					O_WRONLY | O_CREAT | O_APPEND, 0664);
		close(fd);
		i++;
	}
	return (0);
}

int		create_files(t_user *start)
{
	t_list	*lst;
	void	*ptr;

	ptr = start->line;
	while (start->line)
	{
		lst = start->line->content;
		while (lst)
		{
			if (lst->in[0] != NULL)
				if (in_file(lst) == -1)
					return (-1);
			if (lst->out[0] != NULL)
				if (out_file(lst) == -1)
					return (-1);
			lst = lst->next;
		}
		start->line = start->line->next;
	}
	start->line = ptr;
	return (-1);
}
