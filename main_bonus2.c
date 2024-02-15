/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:55:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/02/15 19:31:07 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <string.h>

// the real heredoc seems to write at the end of the existing outfile if it already exists and contains stuffs


// main function checks the number of arguments 
// as the program works from 5 arguments 
// it initiates the structure
// sets j to the number of commands - 1
// then calls functions to create pipes and fork
// waits for as many children as created
// free the ???

int	main(int ac, char **av, char **env)
{
	t_struc	data;
	int		j;

	if (ac < 5)
		ft_printf("Not enough arguments\n");
	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0)
			printf("LOOOO");
			// nbcmd = ac - 4
			// pas de infile parsing
			// prevoir de lire dans le stdin jusqu'au av[2]
		if (struct_init(ac, &data) != 0)
			ft_printf(strerror(errno), 2);
		j = data.nbcmd - 1;
		if (create_pipes(&data) != 0)
			return (1);
		if (ft_fork(av, env, &data) != 0)
			return (1);
		while (j >= 0)
		{
			waitpid(data.pid[j], NULL, 0);
			j--;
		}
		free_tab_int(data.fd, data.nbcmd - 1);
		free(data.pid);
		free(data.cmd);
	}
	return (0);
}

// function creates as many pipes as number of commands minus 1
// then it forks as many times as number of commands
// it enters the childs and depending on which child
// closes the pipes fd and wait for the childs processes
