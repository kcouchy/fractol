# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 15:27:23 by kcouchma          #+#    #+#              #
#    Updated: 2024/01/03 16:44:28 by kcouchma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =						\
			fractol

BONUS_SRCS =				\

INC_FILES = -I libft

SRC = $(addsuffix .c,$(SRCS))
BSRC = $(addsuffix .c,$(BONUS_SRCS))
OBJ = $(addsuffix .o,$(SRCS))
BOBJ = $(addsuffix .o,$(BONUS_SRCS))

CC = cc
CCFLAGS = -Wall -Wextra -Werror -g

NAME = fractol

all: $(NAME)

minilibx-linux-master/libmlx_Linux.a :
	make -C minilibx-linux-master/

$(NAME) : $(OBJ) minilibx-linux-master/libmlx_Linux.a
	make -C libft bonus
	$(CC) -o $@ $(OBJ) libft/libft.a

%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS) $(INC_FILES)

bonus : all

clean :
	make -C libft clean
	rm -rf $(OBJ) $(BOBJ)

fclean : clean
	make -C libft fclean
	rm -rf $(NAME)

re : fclean
	make

.PHONY : all bonus clean fclean re
