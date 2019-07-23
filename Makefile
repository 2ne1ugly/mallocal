ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC=gcc
CFLAGS=-Werror -Wextra -Wall -g -fsanitize=address -Iinclude -Ilibft/include
LIB=-Llibft -lft
LIBFT=libft/libft.a
FRAMEWORK=
SRC=$(shell find src -type f -name '*.c')
NAME=libft_malloc_$(HOSTTYPE).so
OBJ=$(SRC:src/%.c=obj/%.o)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ) $(LIBFT)
	ranlib $(NAME)
	@echo "$(NAME) build complete!"

all: $(NAME)

$(OBJ): obj/%.o : src/%.c
	@mkdir -p $(shell dirname $@) 
	$(CC) $(CFLAGS) -o $@ -c $^

test: $(NAME) main.c
	gcc -Iinclude -Ilibft/include main.c $(SRC) $(LIBFT) -o test

clean:
	@rm -rf obj/

fclean: clean
	@rm -f $(NAME)

re: fclean all
