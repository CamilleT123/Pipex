/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:56:30 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/04 18:15:00 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h> // necessaire pour perror - eliminer tous les printf
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_struc
{
	int		nbcmd;
	int		**fd;
	int		*pid;
	int		fdinfile;
	int		fdoutfile;
	char	*cmd;
	int		i;
	bool	here_doc;
}			t_struc;

int			get_here_doc(char **av);
int			struct_init(int ac, t_struc *data, bool here_doc);

int			create_pipes(t_struc *data);
int			ft_fork(char **av, char **env, t_struc *data);
void		which_process(char **av, char **env, t_struc *data);
int			exec_cmd(char **av, char **env, int fd, t_struc *data);
void		close_higher_fds(t_struc *data);
void		close_below_fds(t_struc *data);

void		dup_reading_fd(t_struc *data);

int			parsing(char **av, char **env, t_struc *data);
int			parsing_files(char **av, t_struc *data);
int			parsing_infile(char **av, t_struc *data);
int			parsing_outfile(char **av, t_struc *data);
int			check_file(char *infile, int i);

int			parsing_cmd(char **av, char **env, t_struc *data);
char		**get_tab(char **av, t_struc *data, char **tab);
char		*get_env(t_struc *data, char **env, char *ptr, char *tab);
char		**get_all_paths(char *ptr);
char		*check_paths(char **paths, char *tab);

int			clean_end(t_struc *data);
void		clean_exit_parent(t_struc *data, int err);
void		clean_exit_here_doc(char *lim, int fd);
int			clean_exit_process(t_struc *data);
int			clean_exit_cmd(t_struc *data, char **arg, int fd);

int			free_tab(char **tab);
int			free_tab_int(int **fd, int nb);

#endif