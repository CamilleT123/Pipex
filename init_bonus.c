/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:58:57 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/29 16:59:12 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	struct_init(int ac, t_struc *data)
{
	int	k;

	k = 0;
	data->nbcmd = ac - 3;
	data->i = 0;
	data->fd = malloc(sizeof(int *) * data->nbcmd - 1);
	if (!data->fd)
		return (1);
	while (k < data->nbcmd - 1)
	{
		data->fd[k] = malloc(sizeof(int) * 2);
		if (!data->fd[k])
			return (1);
		k++;
	}
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		return (1);
	data->fdinfile = 0;
	data->fdoutfile = 0;
	data->cmd = malloc(sizeof(char *) * data->nbcmd);
	if (!data->cmd)
		return (1);
	return (0);
}

int	create_pipes(t_struc *data)
{
	int	l;

	l = 0;
	while (l < data->nbcmd - 1)
	{
		if (pipe(data->fd[l]) == -1)
		{
			ft_printf("%s", strerror(errno));
			return (1);
		}
		l++;
	}
	return (0);
}

int	ft_fork(char **av, char **env, t_struc *data)
{
	while (data->i < data->nbcmd)
	{
		data->pid[data->i] = fork();
		if (data->pid[data->i] < 0)
			return (ft_printf("%s", strerror(errno)), 2);
		if (data->pid[data->i] == 0)
		{
			if (parsing_files(av, data) != 0 || parsing_cmd(av, env, data) != 0)
				return (1);
			which_child(av, env, data);
		}
		if (data->i >= 1)
			close(data->fd[data->i - 1][1]);
		if (data->i >= 2)
			close(data->fd[data->i - 2][0]);
		data->i++;
	}
	return (0);
}
