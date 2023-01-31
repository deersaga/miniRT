# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 12:25:57 by katakagi          #+#    #+#              #
#    Updated: 2023/01/31 17:01:59 by katakagi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC		= cc
SRCS		=	src/main.c\
				src/vec.c\
				src/color.c\
				src/utils.c\
				src/parse.c\
				src/error.c\
				src/get_next_line.c\
				src/get_next_line_utils.c\


SRC_DIR	= src
OBJ_DIR = obj
OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX_DIR	= minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a

INCLUDE		= -I $(MLX_DIR) -I /usr/X11R6/include

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
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME) $(OBJS)

all: $(NAME)

re: fclean all

norm:
	norminette $(SRCS) minirt.h | grep -E -v "TOO_MANY|TOO_LONG"

.PHONY: all clean fcelan re norm
