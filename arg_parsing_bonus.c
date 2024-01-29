/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:57:32 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/29 16:59:35 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	parsing_files(char **av, t_struc *data)
{
	char	*infile;
	char	*outfile;

	if (data->i == 0)
	{
		infile = ft_strdup(av[1]);
		if (check_file(infile, data->i) != 0)
			return (1);
		data->fdinfile = open(infile, O_RDONLY);
		if (data->fdinfile == -1)
			return (ft_putstr_fd(strerror(errno), 2), 2);
	}
	if (data->i == data->nbcmd - 1)
	{
		outfile = ft_strdup(av[data->i + 3]);
		if (check_file(outfile, data->i) != 0)
			return (1);
		data->fdoutfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (data->fdoutfile == -1)
			return (ft_putstr_fd(strerror(errno), 2), 2);
	}
	return (0);
}

int	parsing_cmd(char **av, char **env, t_struc *data)
{
	char	**paths;
	char	**tab;

	paths = get_all_paths(env);
	tab = ft_split(av[data->i + 2], ' ');
	data->cmd[data->i] = check_paths(paths, tab[0]);
	free_tab(tab);
	if (data->cmd[data->i] == NULL)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	return (0);
}

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

// char	*arg_to_cmd(char *av, char **env)
// {
// 	char	**paths;
// 	char	**tab;
// 	char	*pathfinal;

// 	paths = get_all_paths(env);
// 	tab = ft_split(av, ' ');
// 	pathfinal = check_paths(paths, tab[0]);
// 	free_tab(tab);
// 	return (pathfinal);
// }

// char	**arg_to_exec(char *av)
// {
// 	char	**tab;

// 	tab = ft_split(av, ' ');
// 	return (tab);
// }

// char	*arg_to_file(char *av)
// {
// 	char	*file;

// 	file = ft_strdup(av);
// 	return (file);
// }
