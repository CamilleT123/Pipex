/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_clean_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:27:36 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/29 15:40:54 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	return (0);
}

// int	check_outfile(char *outfile)
// {
// 	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
// 	{
// 		ft_putstr_fd("permission denied: ", 2);
// 		ft_putstr_fd(file, 2);
// 		ft_putstr_fd("\n", 2);
// 		return (2);
// 	}
// 	return (0);
// }

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
