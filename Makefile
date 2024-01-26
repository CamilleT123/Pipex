# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 13:55:47 by ctruchot          #+#    #+#              #
#    Updated: 2024/01/26 16:50:10 by ctruchot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c \
		fork.c \
		exec.c \
		arg_parsing.c \
		check_clean.c

SRCB = pipex_bonus.c \
		exec_bonus.c \
		arg_parsing_bonus.c \
		check_clean_bonus.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
includes = pipex.h \
			libft.h
			
OBJ = $(SRC:%.c=%.o)
OBJB = $(SRCB:%.c=%.o)

DEP		= libft/libft.a

all: makelib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Ilibft $< -c -o $@
	
$(NAME): $(OBJ) makelib
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(DEP)
	
bonus: $(OBJB) makelib
	$(CC) $(CFLAGS) $(OBJB) -o $(NAME) $(DEP)

makelib:
	make -C libft
	
clean:
	rm -f $(OBJ)
	rm -f $(OBJB)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re : fclean
	$(MAKE) makelib
	$(MAKE) $(NAME)

.PHONY: all clean fclean re all