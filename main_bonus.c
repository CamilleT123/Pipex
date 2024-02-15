/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:55:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/02/15 18:07:08 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <string.h>

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
