/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:57:32 by ctruchot          #+#    #+#             */
/*   Updated: 2024/02/27 14:41:32 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// gives an fd to infile and outfile, checking the files before
// no need to free anything in the child when we finish with exec
// except if exec fails ???

int	parsing_files(char **av, t_struc *data)
{
	if (data->i == 0)
	{
		if (parsing_infile(av, data) != 0)
			return (1);
	}
	if (data->i == data->nbcmd - 1)
	{
		if (parsing_outfile(av, data) != 0)
			return (1);
	}
	return (0);
}

int	parsing_infile(char **av, t_struc *data)
{
	char	*infile;

	infile = NULL;
	if (data->here_doc == true)
		infile = strdup(".tmpheredoc");
	else
		infile = ft_strdup(av[1]);
	if (infile == NULL)
		return (1);
	if (check_file(infile, data->i) != 0)
		return (free(infile), 1);
	data->fdinfile = open(infile, O_RDONLY);
	if (data->fdinfile == -1)
		return (ft_putstr_fd(strerror(errno), 2), free(infile), 2);
	free(infile);
	return (0);
}

int	parsing_outfile(char **av, t_struc *data)
{
	char	*outfile;

	outfile = NULL;
	if (data->here_doc == true)
		outfile = ft_strdup(av[data->nbcmd + 3]);
	else
		outfile = ft_strdup(av[data->nbcmd + 2]);
	if (outfile == NULL)
		return (1);
	if (check_file(outfile, data->i) != 0)
		return (free(outfile), 1);
	if (data->here_doc == true)
		data->fdoutfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		data->fdoutfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fdoutfile == -1)
		return (ft_putstr_fd(strerror(errno), 2), free(outfile), 2);
	free(outfile);
	return (0);
}

// checks existence and rights on the files

int	check_file(char *file, int i)
{
	if (i == 0 && access(file, F_OK) != 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (access(file, F_OK) == 0 && access(file, R_OK) != 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		return (2);
	}
	if (i != 0 && access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		return (3);
	}
	return (0);
}
