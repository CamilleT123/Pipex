/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:58:57 by ctruchot          #+#    #+#             */
/*   Updated: 2024/02/28 18:04:08 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// initiates each info :
// number of commands is number of arguments -3 for exec file, in and outfile
// fd is an array of array of 2 columns of int
// fd is malloc for number of commands -1 = number of pipes needed
// pid is an array of int
// pid is malloc for number of commands = as many processes as commands
// fdinfile and fdoutfile are set to 0 but will be replaced later

int	struct_init(t_struc *data)
{
	int	k;

	k = -1;
	ft_bzero(data, sizeof(t_struc));
	data->fd = malloc(sizeof(int) * 2);
	if (!data->fd)
		return (clean_exit_parent(data, 1), 1);
	data->pid = malloc(sizeof(int) * 2);
	if (!data->pid)
		return (clean_exit_parent(data, 1), 1);
	return (0);
}
