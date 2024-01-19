/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:09:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/19 16:11:56 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// message d'erreur necessaire pour pid1<0 ?
// 	close(fd[1]); // duplicated ??
// si erreur ds la fonction exec, ne met pas fin a tout le prog car
// si pas de infile + pas bons droits
// sur outfile, les 2 messages s'affichent
// pourtant rien ne doit s'executer?

int	fork1(char **av, char **env, int *fd)
{
	int	pid1;

	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmd1(av[1], av[2], env);
	}
	return (pid1);
}

int	fork2(char **av, char **env, int *fd)
{
	int	pid2;

	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exec_cmd2(av[3], av[4], env);
	}
	return (pid2);
}
