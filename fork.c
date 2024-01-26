/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:09:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/22 15:47:28 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 	close(fd[1]); // duplicated ??

int	fork1(char **av, char **env, int *fd)
{
	int	pid1;

	pid1 = fork();
	if (pid1 < 0)
	{
		ft_printf("%s", strerror(errno));
		return (2);
	}
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (exec_cmd1(av[1], av[2], env) != 0)
			exit (1);
	}
	return (pid1);
}

int	fork2(char **av, char **env, int *fd)
{
	int	pid2;

	pid2 = fork();
	if (pid2 < 0)
	{
		ft_printf("%s", strerror(errno));
		return (3);
	}	
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (exec_cmd2(av[3], av[4], env) != 0)
			exit (2);
	}
	return (pid2);
}
