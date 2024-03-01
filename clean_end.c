/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:27:36 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/01 12:41:27 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// in case of error, free all relevant vars and close fd

int	clean_exit_cmd(t_struc *data, char **arg, int fd)
{
	ft_putstr_fd(strerror(errno), 2);
	if (data->cmd != NULL)
		free(data->cmd);
	if (arg != NULL)
		free_tab(arg);
	close(fd);
	exit(0);
}

// same but at different level
// in case of error, free all relevant vars and close fd

int	clean_exit_process(t_struc *data)
{
	ft_putstr_fd(strerror(errno), 2);
	if (data->cmd != NULL)
		free(data->cmd);
	if (data->i == 0)
	{
		close(data->fdinfile);
		close(data->fd[1]);
	}
	else if (data->i == 1)
	{
		close(data->fdoutfile);
		close(data->fd[0]);
	}
	exit(0);
}
