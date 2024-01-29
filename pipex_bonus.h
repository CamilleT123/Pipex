/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:56:30 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/29 16:57:54 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h> // a quoi sert ?
# include <stdio.h>  // necessaire pour perror - eliminer tous les printf
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h> // pour wait et WEXITSTATUS which returns exit status.
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
	char	**cmd;
	int		i;
}			t_struc;

int			struct_init(int ac, t_struc *data);
int			create_pipes(t_struc *data);
int			ft_fork(char **av, char **env, t_struc *data);
void		which_child(char **av, char **env, t_struc *data);

int			parsing_files(char **av, t_struc *data);
int			parsing_cmd(char **av, char **env, t_struc *data);
int			exec_cmd(char **av, char **env, int fd, t_struc *data);

// int			exec_cmd1(char *av1, char *av2, char **env);
// int			exec_cmdx(char *av1, char **env, int fd);
// int			exec_cmd2(char *av3, char *av4, char **env);

int			check_file(char *infile, int i);
// int			check_outfile(char *outfile);
int			free_tab(char **tab);
int			free_tab_int(int **fd, int nb);

char		**get_all_paths(char **env);
char		*check_paths(char **paths, char *tab);
char		*arg_to_cmd(char *av, char **env);
// char		**arg_to_exec(char *av);
// char		*arg_to_file(char *av);

#endif