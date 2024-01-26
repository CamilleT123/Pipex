/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:55:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/26 17:10:30 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// pipes redirect the output of a command to the input of next command
// to build pipex, launch a new child process for each command
// all commands run at same time but wait the writing end of the pipe
// to be closed before reading from pipe

// function main checks the number of arguments
// if there are 5 arguments, it creates 1 pipe
// then sends to functions for forking
// closes the pipes fd and wait for the childs processes

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (ac < 5)
		ft_printf("Not enough arguments\n");
	if (ac > 5)
		ft_printf("Too much arguments\n");
	if (ac == 5)
	{
		if (pipe(fd) == -1)
		{
			ft_printf("%s", strerror(errno));
			return (1);
		}
		pid1 = fork1(av, env, fd);
		pid2 = fork2(av, env, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid2, NULL, 0);
		waitpid(pid1, NULL, 0);
	}
	return (0);
}
