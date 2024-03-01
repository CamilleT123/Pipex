/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:55:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/02/29 15:04:26 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (ac >= 5)
	{
		if (ac >= 6 && ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			data.here_doc = true;
			if (get_here_doc(av) != 0)
				return (1);
		}
		else
			data.here_doc = false;
		if (struct_init(ac, &data, data.here_doc) != 0)
			return (1);
		create_pipes(&data);
		if (ft_fork(av, env, &data) != 0)
			return (1);
		clean_end(&data);
	}
	return (0);
}
