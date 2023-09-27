NAME := cub
CC := cc
CFLAGS := -Wall -Wextra -Werror
SRCS := cub3d.c
OBJ_DIR := obj
SRC_DIR := src
SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP = mkdir -p $(@D)
LIBS_TARGET := mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) -o $@ $^ -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz -Llibft/ -g3

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -Iinclude -Imlx -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

update:
	git stash
	git pull
	git submodule update --init
	git stash pops
