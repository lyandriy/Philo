SRC = main.c \
	  philo.c \
	  utils.c \
	  thread.c \
	  make_it.c \
	  checker_input.c \
	  life_or_dead.c \
	  lunch.c \
	  print.c \

OBJ = $(SRC:.c=.o)

NAME = philo

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3

all: $(NAME)

debug: CFLAGS += -g3 -fsanitize=thread#-fsanitize=address
debug: re

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re