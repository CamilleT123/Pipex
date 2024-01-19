/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:56:30 by ctruchot          #+#    #+#             */
/*   Updated: 2024/01/19 16:16:48 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <errno.h> // utilise ?
# include <fcntl.h>
# include <limits.h>
# include <stddef.h> // a quoi sert ?
# include <stdio.h>  // necessaire pour perror - eliminer tous les printf
# include <stdlib.h>
# include <sys/wait.h> // pour wait et WEXITSTATUS which returns exit status.
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		fork1(char **av, char **env, int *fd);
int		fork2(char **av, char **env, int *fd);

int		exec_cmd1(char *av1, char *av2, char **env);
int		exec_cmd2(char *av3, char *av4, char **env);

int		check_infile(char *infile);
int		check_outfile(char *outfile);
int		free_tab(char **tab);
char	**get_all_paths(char **env);
char	*check_paths(char **paths, char *tab);
char	*arg_to_cmd(char *av, char **env);
char	**arg_to_exec(char *av);
char	*arg_to_file(char *av);

#endif