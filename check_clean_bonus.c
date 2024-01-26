/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_clean_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:27:36 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/26 18:10:42 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_infile(char *infile)
{
	if (access(infile, F_OK) != 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (access(infile, F_OK) == 0 && access(infile, R_OK) != 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putstr_fd("\n", 2);
		return (2);
	}
	return (0);
}

int	check_outfile(char *outfile)
{
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) != 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(outfile, 2);
		ft_putstr_fd("\n", 2);
		return (2);
	}
	return (0);
}

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

int	free_tab_int(int **fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	return (0);
}
