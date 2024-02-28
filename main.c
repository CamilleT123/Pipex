/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:55:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/02/28 18:04:18 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// main function checks the number of arguments
// as the program works from 5 arguments.
// it initiates the structure
// sets j to the number of commands - 1
// then calls functions to create pipes and fork
// waits for as many children as created
// free the various elements

int	main(int ac, char **av, char **env)
{
	t_struc	data;

	if (ac < 5)
		return (ft_printf("Not enough arguments\n"), 1);
	if (ac > 5)
		ft_printf("Too much arguments\n");
	if (ac == 5)
	{
		if (struct_init(&data) != 0)
			return (1);
		if (pipe(data.fd) == -1)
		{
			ft_printf("%s", strerror(errno));
			clean_exit_parent(&data, 1);
			exit(2);
			return (1);
		}
		ft_fork(av, env, &data);
		waitpid(data.pid[0], NULL, 0);
		waitpid(data.pid[1], NULL, 0);
		clean_exit_parent(&data, 0);
	}
	return (0);
}
