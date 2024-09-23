/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_cmd_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:51:20 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/04 17:02:53 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_tab(char **av, t_struc *data, char **tab)
{
	if (data->here_doc == true)
		tab = ft_split(av[data->i + 3], ' ');
	else
		tab = ft_split(av[data->i + 2], ' ');
	return (tab);
}

char	*get_env(t_struc *data, char **env, char *ptr, char *tab)
{
	int	i;

	i = 0;
	while (ptr == NULL && env[i])
	{
		ptr = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	if (ptr == NULL)
	{
		if (access(tab, F_OK | X_OK) == 0)
		{
			data->cmd = tab;
			return (NULL);
		}
		else
			return (ft_putstr_fd("No path", 2), NULL);
	}
	else
		return (ptr);
}

// for the commands, gets all the possible paths provided by env and
// checks all of them

int	parsing_cmd(char **av, char **env, t_struc *data)
{
	char	**paths;
	char	**tab;
	char	*ptr;

	tab = NULL;
	ptr = NULL;
	tab = get_tab(av, data, tab);
	if (tab == NULL)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	ptr = get_env(data, env, ptr, tab[0]);
	if (ptr == NULL)
	{
		if (data->cmd == NULL)
			return (free_tab(tab), 1);
		return (0);
	}
	paths = get_all_paths(ptr);
	if (paths == NULL)
		return (free_tab(tab), 1);
	data->cmd = check_paths(paths, tab[0]);
	if (data->cmd == NULL)
		return (free_tab(tab), 1);
	return (0);
}

// gets all the possible paths, splitting them

char	**get_all_paths(char *ptr)
{
	char	**paths;

	ptr = ft_substr(ptr, 5, ft_strlen(ptr));
	paths = ft_split(ptr, ':');
	if (paths == NULL)
	{
		if (ptr != NULL)
			free(ptr);
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	free(ptr);
	return (paths);
}

// checks all possible paths to keep only the valid path

char	*check_paths(char **paths, char *tab)
{
	int		i;
	char	*cpypath;
	char	*cpypath2;

	cpypath2 = NULL;
	i = 0;
	if (access(tab, F_OK | X_OK) == 0)
		return (free_tab(paths), tab);
	while (paths[i])
	{
		if (cpypath2 != NULL)
			free(cpypath2);
		cpypath = ft_strjoin(paths[i], "/");
		cpypath2 = ft_strjoin(cpypath, tab);
		free(cpypath);
		if (access(cpypath2, F_OK | X_OK) == 0)
			return (free_tab(paths), cpypath2);
		i++;
	}
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(tab, 2);
	ft_putstr_fd("\n", 2);
	return (free_tab(paths), free(cpypath2), NULL);
}
