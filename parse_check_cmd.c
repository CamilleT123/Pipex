/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:51:20 by ctruchot          #+#    #+#             */
/*   Updated: 2024/02/28 17:58:35 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// for the commands, gets all the possible paths provided by env and
// checks all of them

int	parsing_cmd(char **av, char **env, t_struc *data)
{
	char	**paths;
	char	**tab;

	tab = NULL;
	paths = get_all_paths(env);
	if (paths == NULL)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	tab = ft_split(av[data->i + 2], ' ');
	if (tab == NULL)
		return (ft_putstr_fd(strerror(errno), 2), free_tab(paths), 1);
	data->cmd = check_paths(paths, tab[0]);
	free_tab(tab);
	if (data->cmd == NULL)
		return (1);
	return (0);
}

// gets all the possible paths, splitting them

char	**get_all_paths(char **env)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = NULL;
	while (path == NULL)
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	path = ft_substr(path, 5, ft_strlen(path));
	paths = ft_split(path, ':');
	if (paths == NULL)
	{
		if (path != NULL)
			free(path);
		return (NULL);
	}
	free(path);
	return (paths);
}

// checks all possible paths to keep only the valid path

char	*check_paths(char **paths, char *tab)
{
	int		i;
	char	*cpypath;
	char	*cpypath2;
	char	*pathfinal;

	i = 0;
	while (paths[i])
	{
		cpypath = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(cpypath);
		cpypath2 = paths[i];
		paths[i] = ft_strjoin(paths[i], tab);
		free(cpypath2);
		if (access(paths[i], F_OK | R_OK) == 0)
		{
			pathfinal = ft_strdup(paths[i]);
			return (free_tab(paths), pathfinal);
		}
		i++;
	}
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(&tab[0], 2);
	ft_putstr_fd("\n", 2);
	return (free_tab(paths), NULL);
}
