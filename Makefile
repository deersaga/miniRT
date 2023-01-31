# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 12:25:57 by katakagi          #+#    #+#              #
#    Updated: 2023/01/31 14:38:35 by susami           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC		= cc
SRCS		=	src/main.c\
				src/vec.c

SRC_DIR	= src
OBJ_DIR = obj
OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX_DIR	= minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a

INCLUDE		= -I $(MLX_DIR)

CFLAGS		= -Wall -Wextra -Werror $(INCLUDE)
DFLAGS		= -g -fsanitize=address -Weverything

FRAMEWORK	= -framework OpenGL -framework AppKit
LIBPATH		=-lmlx -lX11 -lXext	-L$(MLX_DIR) -L/usr/X11R6/lib

$(NAME): $(OBJS) $(MLX)
	echo $(OBJS)
	$(CC) $(LIBPATH) $(FRAMEWORK) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@);
	echo hello
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm $(OBJS)

fclean:
	rm $(NAME) $(OBJS)

all: $(NAME)

re: fclean all

norm:
	norminette $(SRCS) minirt.h | grep -v "TOO_MANY"

.PHONY: all clean fcelan re norm
