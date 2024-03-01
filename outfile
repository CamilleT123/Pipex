# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 13:55:47 by ctruchot          #+#    #+#              #
#    Updated: 2024/03/01 12:40:54 by ctruchot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

SRC = main.c \
		exec.c \
		parse_check_files.c \
		parse_check_cmd.c \
		utils.c \
		clean_end.c

SRCB = main_bonus.c \
		init_bonus.c \
		exec_bonus.c \
		parse_check_files_bonus.c \
		parse_check_cmd_bonus.c \
		utils_bonus.c \
		clean_end_bonus.c
		
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
includes = pipex.h \
			libft.h \
			get_next_line.h
			
OBJ = $(SRC:%.c=%.o)
OBJB = $(SRCB:%.c=%.o)

DEP		= libft/libft.a \
			GNL/get_next_line.a

all: $(NAME)
bonus: $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -Ilibft -IGNL $< -c -o $@
	
$(NAME): $(OBJ) 
	$(MAKE) makelib
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(DEP)

$(NAME_BONUS): $(OBJB) 
	$(MAKE) makelib
	$(CC) $(CFLAGS) $(OBJB) -o $(NAME_BONUS) $(DEP)

makelib:
	make -C libft
	make -C GNL
	
clean:
	rm -f $(OBJ)
	rm -f $(OBJB)
	make clean -C libft
	make clean -C GNL

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	make fclean -C libft
	make fclean -C GNL

re : fclean
	$(MAKE) makelib
	$(MAKE) $(NAME)

.PHONY: all bonus clean fclean re all