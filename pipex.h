/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:56:30 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/01 12:20:22 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h> 
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_struc
{
	int		fd[2];
	int		pid[2];
	int		fdinfile;
	int		fdoutfile;
	char	*cmd;
	int		i;
}			t_struc;

int			struct_init(t_struc *data);

int			create_pipes(t_struc *data);
int			ft_fork(char **av, char **env, t_struc *data);
void		which_process(char **av, char **env, t_struc *data);
int			exec_cmd(char **av, char **env, int fd, t_struc *data);

int			parsing_files(char **av, t_struc *data);
int			parsing_infile(char **av, t_struc *data);
int			parsing_outfile(char **av, t_struc *data);
int			check_file(char *infile, int i);

int			parsing_cmd(char **av, char **env, t_struc *data);
char		**get_all_paths(char **env);
char		*check_paths(char **paths, char *tab);

void		clean_exit_parent(t_struc *data, int err);
int			clean_exit_process(t_struc *data);
int			clean_exit_cmd(t_struc *data, char **arg, int fd);

int			free_tab(char **tab);
int			free_tab_int(int **fd, int nb);

#endif