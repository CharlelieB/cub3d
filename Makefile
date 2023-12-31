NAME := cub3D
CC := cc
CFLAGS := -Wall -Wextra -Werror
DIR_DUP = mkdir -p $(@D)
OBJ_DIR := obj
SRC_DIR := src
SRCS := main.c render.c move.c dda.c keys.c parsing.c parsing_textures.c textures.c \
		parsing_utils.c parsing_utils2.c parsing_map.c mlx_utils.c cub3d.c raycasting.c floor.c
SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBS_TARGET := mlx/libmlx.a libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) -o $@ $^ -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz -Llibft/ -lft

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -Iinclude -Imlx -Ilibft/include -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

sub:
	git submodule update --init

.PHONY: all clean fclean re