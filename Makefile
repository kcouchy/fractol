# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 15:27:23 by kcouchma          #+#    #+#              #
#    Updated: 2024/01/09 18:15:30 by kcouchma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =						\
			check_inputs	\
			fractol			\
			hooks			\
			build

BONUS_SRCS =				\

INC_FILES = -I libft

INC_ARCHIVES = libft/libft.a minilibx-linux-master/libmlx_Linux.a

LINKS = -L minilibx-linux-master/ -lmlx -lXext -lX11

SRC = $(addsuffix .c,$(SRCS))
BSRC = $(addsuffix .c,$(BONUS_SRCS))
OBJ = $(addsuffix .o,$(SRCS))
BOBJ = $(addsuffix .o,$(BONUS_SRCS))

CC = cc
CCFLAGS = -Wall -Wextra -Werror -Ofast

NAME = fractol

all: $(NAME)

$(NAME) : $(OBJ)
	make -C libft bonus
	make -C minilibx-linux-master/
	$(CC) -o $@ $(OBJ) $(INC_ARCHIVES) $(LINKS)

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
