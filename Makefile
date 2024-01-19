# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 13:55:47 by ctruchot          #+#    #+#              #
#    Updated: 2024/01/19 16:16:20 by ctruchot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c \
		fork.c \
		exec.c \
		arg_parsing.c \
		check_clean.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
includes = pipex.h \
			libft.h
			
OBJ = $(SRC:%.c=%.o)

DEP		= libft/libft.a
# args = arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}

all: makelib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Ilibft $< -c -o $@
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(DEP)

# $(NAME): $(OBJ) $(includes)
# 	$(CC) $(OBJ)

makelib:
	make -C libft
	
clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re : fclean
	$(MAKE) makelib
	$(MAKE) $(NAME)

.PHONY: all clean fclean re all