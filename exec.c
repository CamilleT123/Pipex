/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:56:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/22 14:52:02 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	dup2(fdfile, 1);
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
