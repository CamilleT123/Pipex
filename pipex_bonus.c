/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:55:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/26 19:10:41 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <string.h>

// main function checks the number of arguments as the program works from 5 arguments

int	main(int ac, char **av, char **env)
{
	t_struc data;
	int i;
	
	if (ac < 5)
		ft_printf("Not enough arguments\n");
	if (ac >= 5)
	{
		i = data.nbcmd - 1;
		struct_init(ac, av, env, &data);
		if (create_pipes(&data) != 0)
			return (1); // prevoir message erreur ?
		if (ft_fork(&data) != 0)
			return (1); // prevoir message erreur ?
		while (i >= 0)
		{
			waitpid(data.pid[i], NULL, 0);
			i--;
		}
		free_tab_int(data.fd, data.nbcmd - 1);
		free(data.pid);
	}
	return (0);
}

// function creates as many pipes as number of commands minus 1
// then it forks as many times as number of commands
// it enters the childs and depending on which child
// closes the pipes fd and wait for the childs processes



