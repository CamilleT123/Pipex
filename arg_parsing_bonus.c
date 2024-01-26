/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:57:32 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/26 16:51:19 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	free(path);
	return (paths);
}

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

char	*arg_to_cmd(char *av, char **env)
{
	char	**paths;
	char	**tab;
	char	*pathfinal;

	paths = get_all_paths(env);
	tab = ft_split(av, ' ');
	pathfinal = check_paths(paths, tab[0]);
	free_tab(tab);
	return (pathfinal);
}

char	**arg_to_exec(char *av)
{
	char	**tab;

	tab = ft_split(av, ' ');
	return (tab);
}

char	*arg_to_file(char *av)
{
	char	*file;

	file = ft_strdup(av);
	return (file);
}
