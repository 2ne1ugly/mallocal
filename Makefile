ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC=clang
CFLAGS=-Werror -Wextra -Wall -g -Iincludes -Ilibft
LFLAGS=-Llibft/ -lft
SRC=$(wildcard src/*)
NAME=libft_malloc_$(HOSTTYPE).so
OBJ=$(SRC:src/%.c=%.o)
SHELL := /bin/bash

.PHONY: clean fclean all re norm norme debug test norman update

VPATH = src obj includes

$(NAME): $(OBJ)
	ar rc $(NAME) obj/*	libft/libft.a
	ranlib $(NAME)
	@echo "$(NAME) build complete!"

all: $(NAME)

%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -o obj/$@ -c $<

clean:
	@rm -rf obj/

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	norminette src/. includes/.

test:
	$(CC) main.c src/*c $(CFLAGS) $(LFLAGS) -o test

norme: norm

norman:
	-norminette * | grep -iv warning