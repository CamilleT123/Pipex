/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_end_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:27:36 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/04 18:09:08 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// at the end of the main, waits for each child and end the parent

int	clean_end(t_struc *data)
{
	int	j;

	j = data->nbcmd;
	while (--j >= 0)
		waitpid(data->pid[j], NULL, 0);
	clean_exit_parent(data, 0);
	return (0);
}

// to end parent, free all malloc vars and delete the temporary heredoc file

void	clean_exit_parent(t_struc *data, int err)
{
	if (err == 1)
		ft_putstr_fd(strerror(errno), 2);
	if (data->fd != NULL)
		free_tab_int(data->fd, data->nbcmd - 1);
	if (data->pid != NULL)
		free(data->pid);
	if (access(".tmpheredoc", F_OK) == 0)
	{
		if (unlink(".tmpheredoc") != 0)
		{
			ft_putstr_fd(strerror(errno), 2);
		}
	}
}

// in case of error in get_here_doc

void	clean_exit_here_doc(char *lim, int fd)
{
	ft_putstr_fd(strerror(errno), 2);
	if (lim != NULL)
		free(lim);
	close(fd);
	if (access(".tmpheredoc", F_OK) == 0)
	{
		if (unlink(".tmpheredoc") != 0)
		{
			ft_putstr_fd(strerror(errno), 2);
		}
	}
}

// in case of error, free all relevant vars and close fd

int	clean_exit_cmd(t_struc *data, char **arg, int fd)
{
	ft_putstr_fd(strerror(errno), 2);
	if (data->cmd != NULL)
		free(data->cmd);
	if (arg != NULL)
		free_tab(arg);
	close(fd);
	clean_exit_parent(data, 0);
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
		close(data->fd[0][1]);
	}
	else if (data->i == data->nbcmd - 1)
	{
		close(data->fdoutfile);
		close(data->fd[data->i - 1][0]);
	}
	else
	{
		close(data->fd[data->i - 1][0]);
		close(data->fd[data->i][1]);
	}
	clean_exit_parent(data, 0);
	exit(0);
}
