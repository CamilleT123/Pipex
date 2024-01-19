/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:56:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/19 16:14:37 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// revoir quel message d'erreur si execve =-1

int	exec_cmd1(char *av1, char *av2, char **env)
{
	char	*cmd;
	char	**arg;
	int		fdfile;
	char	*infile;

	cmd = arg_to_cmd(av2, env);
	arg = arg_to_exec(av2);
	infile = arg_to_file(av1);
	if (check_infile(infile) != 0)
	{
		return (1);
	}
	fdfile = open(infile, O_RDONLY);
	if (fdfile == -1)
		return (2);
	dup2(fdfile, STDIN_FILENO);
	close(fdfile);
	if (execve(cmd, arg, env) == -1)
	{
		perror("command not found");
		return (2);
	}
	free(cmd);
	free_tab(arg);
	return (0);
}

int	exec_cmd2(char *av3, char *av4, char **env)
{
	char	*cmd;
	char	**arg;
	char	*outfile;
	int		fdfile;

	cmd = arg_to_cmd(av3, env);
	arg = arg_to_exec(av3);
	outfile = arg_to_file(av4);
	if (check_outfile(outfile) != 0)
		return (1);
	fdfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fdfile == -1)
		return (2);
	dup2(fdfile, 1);
	close(fdfile);
	if (execve(cmd, arg, env) == -1)
	{
		ft_putstr_fd("\n\ncould not find program\n\n", 2);
		return (2);
	}
	free(cmd);
	free_tab(arg);
	return (0);
}
