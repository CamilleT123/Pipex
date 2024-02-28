/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:58:57 by ctruchot          #+#    #+#             */
/*   Updated: 2024/02/28 15:55:15 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// for here_doc, creates a temporary document "heredoc",
// writes what is sent to the stdin until the LIMITER signal

int	get_here_doc(char **av)
{
	char	*lim;
	char	*line;
	int		fd;

	lim = NULL;
	line = NULL;
	lim = ft_strjoin(av[2], "\n");
	if (lim == NULL)
		exit(2);
	fd = open(".tmpheredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (clean_exit_here_doc(lim, fd), 1);
	line = get_next_line(0);
	if (line == NULL)
		return (clean_exit_here_doc(lim, fd), 1);
	while (ft_strncmp(line, lim, ft_strlen(lim)) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
		if (line == NULL)
			return (clean_exit_here_doc(lim, fd), 1);
	}
	return (free(line), free(lim), close(fd), 0);
}

// initiates each info :
// number of commands is number of arguments -3 for exec file, in and outfile
// fd is an array of array of 2 columns of int
// fd is malloc for number of commands -1 = number of pipes needed
// pid is an array of int
// pid is malloc for number of commands = as many processes as commands
// fdinfile and fdoutfile are set to 0 but will be replaced later

int	struct_init(int ac, t_struc *data, bool here_doc)
{
	int	k;

	k = -1;
	ft_bzero(data, sizeof(t_struc));
	if (here_doc == true)
		data->here_doc = true;
	data->nbcmd = ac - 3;
	if (data->here_doc == true)
		data->nbcmd = ac - 4;
	data->fd = malloc(sizeof(int *) * data->nbcmd - 1);
	if (!data->fd)
		return (clean_exit_parent(data, 1), 1);
	while (++k < data->nbcmd - 1)
	{
		data->fd[k] = malloc(sizeof(int) * 2);
		if (!data->fd[k])
			return (clean_exit_parent(data, 1), 1);
	}
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		return (clean_exit_parent(data, 1), 1);
	return (0);
}
