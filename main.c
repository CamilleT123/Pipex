/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:55:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/01 12:41:09 by ctruchot         ###   ########.fr       */
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
		ft_bzero(&data, sizeof(t_struc));
		if (pipe(data.fd) == -1)
			return (ft_putstr_fd(strerror(errno), 2), 1);
		if (ft_fork(av, env, &data) != 0)
			return (1);
		waitpid(data.pid[0], NULL, 0);
		waitpid(data.pid[1], NULL, 0);
	}
	return (0);
}
