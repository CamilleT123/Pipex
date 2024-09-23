/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:56:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/04 13:17:26 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// i is the index of processes and there is one process per command.
// function forks as many times as number of commands
// it then enters the childs and parses the files and commands.
// depending on which child closes the pipes fd

// i = 0 is the first reading process on the infile and
// i= nbcmd -1 is the last writing process in the outfile

int	ft_fork(char **av, char **env, t_struc *data)
{
	while (data->i < 2)
	{
		data->pid[data->i] = fork();
		if (data->pid[data->i] < 0)
			return (ft_putstr_fd(strerror(errno), 2), 2);
		if (data->pid[data->i] == 0)
		{
			if (parsing_files(av, data) != 0 || parsing_cmd(av, env, data) != 0)
			{
				close(data->fd[1]);
				close(data->fd[0]);
				close(data->fdinfile);
				close(data->fdoutfile);
				exit (1);
			}
			which_process(av, env, data);
		}
		data->i++;
	}
	close(data->fd[0]);
	close(data->fd[1]);
	return (0);
}

// depending on the i (i.e which command is processed),
// closes and dup the relevant fd

void	which_process(char **av, char **env, t_struc *data)
{
	if (data->i == 0)
	{
		close(data->fd[0]);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			clean_exit_process(data);
		close(data->fd[1]);
		exec_cmd(av, env, data->fdinfile, data);
	}
	if (data->i == 1)
	{
		close(data->fd[1]);
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			clean_exit_process(data);
		close(data->fd[0]);
		exec_cmd(av, env, data->fdoutfile, data);
	}
}

// depending also on the i, dup the standard in or output
// and executes the command

int	exec_cmd(char **av, char **env, int fd, t_struc *data)
{
	char	**arg;
	int		fdstd;

	fdstd = STDOUT_FILENO;
	if (data->i == 0)
		fdstd = STDIN_FILENO;
	arg = ft_split(av[data->i + 2], ' ');
	if (arg == NULL)
		return (clean_exit_cmd(data, arg, fd));
	if (dup2(fd, fdstd) == -1)
		return (clean_exit_cmd(data, arg, fd));
	close(fd);
	if (execve(data->cmd, arg, env) == -1)
		return (clean_exit_cmd(data, arg, fd));
	return (0);
}
