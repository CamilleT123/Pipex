# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 13:55:47 by ctruchot          #+#    #+#              #
#    Updated: 2024/02/27 18:05:50 by ctruchot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = main.c \
		init.c \
		exec.c \
		parse_check_files.c \
		parse_check_cmd.c \
		utils.c \
		clean_end.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
includes = pipex.h \
			libft.h \
			get_next_line.h
			
OBJ = $(SRC:%.c=%.o)

DEP		= libft/libft.a \
			GNL/get_next_line.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Ilibft -IGNL $< -c -o $@
	
$(NAME): $(OBJ) 
	$(MAKE) makelib
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(DEP)

makelib:
	make -C libft
	make -C GNL
	
clean:
	rm -f $(OBJ)
	make clean -C libft
	make clean -C GNL

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make fclean -C GNL

re : fclean
	$(MAKE) makelib
	$(MAKE) $(NAME)

.PHONY: all clean fclean re all