# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 13:55:47 by ctruchot          #+#    #+#              #
#    Updated: 2024/02/15 19:19:35 by ctruchot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
NAME_BONUS2 = pipex_bonus2


SRC = main.c \
		fork.c \
		exec.c \
		arg_parsing.c \
		check_clean.c

SRCB = main_bonus.c \
		init_bonus.c \
		exec_bonus.c \
		arg_parsing_bonus.c \
		check_clean_bonus.c

SRCB2 = main_bonus2.c \
		init_bonus.c \
		exec_bonus.c \
		arg_parsing_bonus.c \
		check_clean_bonus.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
includes = pipex.h \
			libft.h
			
OBJ = $(SRC:%.c=%.o)
OBJB = $(SRCB:%.c=%.o)
OBJB2 = $(SRCB2:%.c=%.o)

DEP		= libft/libft.a

all: $(NAME)
bonus: $(NAME_BONUS)
bonus2: $(NAME_BONUS2)


%.o: %.c
	$(CC) $(CFLAGS) -Ilibft $< -c -o $@
	
$(NAME): $(OBJ) 
	$(MAKE) makelib
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(DEP)
	
$(NAME_BONUS): $(OBJB) 
	$(MAKE) makelib
	$(CC) $(CFLAGS) $(OBJB) -o $(NAME_BONUS) $(DEP)

$(NAME_BONUS2): $(OBJB2) 
	$(MAKE) makelib
	$(CC) $(CFLAGS) $(OBJB2) -o $(NAME_BONUS2) $(DEP)

makelib:
	make -C libft
	
clean:
	rm -f $(OBJ)
	rm -f $(OBJB)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -f $(NAME_BONUS2)
	make fclean -C libft

re : fclean
	$(MAKE) makelib
	$(MAKE) $(NAME)

.PHONY: all clean fclean re all