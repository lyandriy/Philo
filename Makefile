# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/22 16:50:19 by lyandriy          #+#    #+#              #
#    Updated: 2023/10/27 20:24:37 by lyandriy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  philo.c \
	  utils.c \
	  thread.c \
	  make_it.c \
	  checker_input.c \
	  life_or_dead.c \
	  lunch.c \
	  utils_thred.c \

OBJ = $(SRC:.c=.o)

NAME = philo

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3
all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re