/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:56:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/26 19:08:34 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int struct_init(int ac, char **av, char **env, t_struc *data)
{
	int i;
	
	i = 0;
	data->nbcmd = ac - 3; // pour 3 commandes - ac = 6 et max = 3 mais  1 pipe de moins
	data->arg = av ;
	data->env = env;
	data->fd = malloc(sizeof(int *) * data->nbcmd - 1);
	if (!data->fd)
		return (0);
	while (i < data->nbcmd - 1)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (!data->fd[i])
			return (0);
		i++;
	}
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		return (0);
	return (1);
}
int create_pipes(t_struc *data)
{
	int i;
	i = 0;
	while (i < data->nbcmd - 1)
	{
		if (pipe(data->fd[i]) == -1)
		{
			ft_printf("%s", strerror(errno));
			return (1);
		}
		i++;
	}
	return (0);
}
int	ft_fork(t_struc *data)
{
	int i;
	int	pid;
	
	i = 0;
	pid = 0;
	while (i < data->nbcmd) // i = 0, i = 1, i = 2 donc 3 forks et 3 enfants pour 3 commandes
	{
		data->pid[i] = fork();
		if (pid < 0)
		{
			ft_printf("%s", strerror(errno));
				return (2);
		}
		if (data->pid[i] == 0)
			which_child(data->arg, data->env, i, data);
		if (i >= 1)
			close(data->fd[i-1][1]);
		if (i >= 2)
			close(data->fd[i-2][0]);
		i++;
	}
	return (0);
}

void which_child(char **av, char **env, int i, t_struc *data)
{  // pour i = 0 // on est dans le 1er enfant et 1er pipe donc data.fd[0][0] et data.fd[0][1]
	if (i == 0)
	{
		close(data->fd[0][0]); 
		dup2(data->fd[0][1], STDOUT_FILENO);
		close(data->fd[0][1]);
		if (exec_cmd1(av[1], av[2], env) != 0)
			exit (1);
	} // pour i = 1 // on est dans le 2e enfant / lecture du 1er pipe
	if (i > 0 && i < data->nbcmd - 1)
	{
		close(data->fd[i][0]);
		close(data->fd[i-1][1]);
		dup2(data->fd[i-1][0], STDIN_FILENO);
		close(data->fd[i-1][0]);
		if (exec_cmdx(av[i + 2], env, data->fd[i][1]) != 0)
			exit (2);
	} // pour i = 2 // on est dans le 3e enfant / lecture du 2e pipe
	if (i == data->nbcmd - 1)
	{
		close(data->fd[i - 1][1]);
		dup2(data->fd[i - 1][0], STDIN_FILENO);
		close(data->fd[i - 1][0]);
		if (exec_cmd2(av[i + 2], av[i + 3], env) != 0)
			exit (2);
	}
}

int	exec_cmd1(char *av1, char *av2, char **env)
{
	char	*cmd;
	char	**arg;
	int		fdfile;
	char	*infile;

	infile = arg_to_file(av1);
	if (check_infile(infile) != 0)
		return (1);
	cmd = arg_to_cmd(av2, env);
	if (cmd == NULL)
		return (1);
	arg = arg_to_exec(av2);
	fdfile = open(infile, O_RDONLY);
	if (fdfile == -1)
		return (ft_putstr_fd(strerror(errno), 2), 2);
	dup2(fdfile, STDIN_FILENO);
	close(fdfile);
	if (execve(cmd, arg, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		free(cmd);
		free_tab(arg);
		return (3);
	}
	return (0);
}

int	exec_cmdx(char *av3, char **env, int fd)
{
	char	*cmd;
	char	**arg;
	
	cmd = arg_to_cmd(av3, env);
	if (cmd == NULL)
		return (1);
	arg = arg_to_exec(av3);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	(void)fd;
	if (execve(cmd, arg, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		free(cmd);
		free_tab(arg);
		return (3);
	}
	return (0);
}

int	exec_cmd2(char *av3, char *av4, char **env)
{
	char	*cmd;
	char	**arg;
	char	*outfile;
	int		fdfile;

	outfile = arg_to_file(av4);
	if (check_outfile(outfile) != 0)
		return (1);
	cmd = arg_to_cmd(av3, env);
	if (cmd == NULL)
		return (1);
	arg = arg_to_exec(av3);
	fdfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fdfile == -1)
		return (ft_putstr_fd(strerror(errno), 2), 2);
	dup2(fdfile, STDOUT_FILENO);
	close(fdfile);
	if (execve(cmd, arg, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		free(cmd);
		free_tab(arg);
		return (3);
	}
	return (0);
}
