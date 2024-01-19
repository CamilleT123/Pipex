/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:55:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/19 16:15:49 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> // replace all printf by ft_printf

// pipes redirect the output of a command to the input of next command
// to build pipex, launch a new child process for each command
// all commands run at same time but wait the writing end of the pipe
// to be closed before reading from pipe

// Check the existence of infile and outfile - ok
// if infile does not exits : no such file or directory: infile - ok
// if outfile does not exist, > creates one to write in it
// quid si existe mais pas les droits necessairs ?

// message d'erreur si pas 4 arguments?
// message d'erreur necessaire pour pipe(fd) == -1?
int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			return (1);
		pid1 = fork1(av, env, fd);
		pid2 = fork2(av, env, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid2, NULL, 0);
		waitpid(pid1, NULL, 0);
	}
	return (0);
}

// int wstatus1;
// waitpid(pid1, &wstatus1, 0);
// if (WIFEXITED(wstatus1) != 0)
// {
// 	int statuscode = WEXITSTATUS(wstatus1);
// 	if (statuscode == 0)
// 		printf("normal finish\n");
// 	else
// 		printf("failure with status code %d\n", statuscode);
// }
// printf("processing finished\n");

// // replace standard input with input file
// // replace standard output with output file
// // close unused file descriptors

// // execute grep // pas compris la def
// // grep va chercher dans /usr/bin car binary
// // lui indiquer le chemin via env
// // printf chaque ligne de env - celle qui ns interesse est path
// // recuperer le path et essayer de l'access via access

// // si ac est superieur a 5, on ne gere pas -> prevoir un message d'erreur ?
// if (ac > 5)

// // si ac est inferieur a 5, en theorie,
// ca fonctionne dans une certaine mesure
	// if (ac < 5)
