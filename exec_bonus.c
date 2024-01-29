/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:56:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/29 17:00:32 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	which_child(char **av, char **env, t_struc *data)
{
	if (data->i == 0)
	{
		close(data->fd[0][0]);
		dup2(data->fd[0][1], STDOUT_FILENO);
		close(data->fd[0][1]);
		if (exec_cmd(av, env, data->fdinfile, data) != 0)
			exit(1);
	}
	if (data->i > 0 && data->i < data->nbcmd - 1)
	{
		close(data->fd[data->i][0]);
		close(data->fd[data->i - 1][1]);
		dup2(data->fd[data->i - 1][0], STDIN_FILENO);
		close(data->fd[data->i - 1][0]);
		if (exec_cmd(av, env, data->fd[data->i][1], data) != 0)
			exit(2);
	}
	if (data->i == data->nbcmd - 1)
	{
		close(data->fd[data->i - 1][1]);
		dup2(data->fd[data->i - 1][0], STDIN_FILENO);
		close(data->fd[data->i - 1][0]);
		if (exec_cmd(av, env, data->fdoutfile, data) != 0)
			exit(2);
	}
}

int	exec_cmd(char **av, char **env, int fd, t_struc *data)
{
	char	**arg;

	arg = ft_split(av[data->i + 2], ' ');
	if (data->i == 0)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	if (execve(data->cmd[data->i], arg, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		free(data->cmd[data->i]);
		free_tab(arg);
		return (3);
	}
	return (0);
}

// int	exec_cmdx(char *av3, char **env, int fd)
// {
// 	char	**arg;

// 	arg = arg_to_exec(av3);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	(void)fd;
// 	if (execve(cmd, arg, env) == -1)
// 	{
// 		ft_putstr_fd(strerror(errno), 2);
// 		free(cmd);
// 		free_tab(arg);
// 		return (3);
// 	}
// 	return (0);
// }

// int	exec_cmd2(char *av3, char *av4, char **env)
// {
// 	char	**arg;

// 	dup2(fdfile, STDOUT_FILENO);
// 	close(fdfile);
// 	if (execve(cmd, arg, env) == -1)
// 	{
// 		ft_putstr_fd(strerror(errno), 2);
// 		free(cmd);
// 		free_tab(arg);
// 		return (3);
// 	}
// 	return (0);
// }
