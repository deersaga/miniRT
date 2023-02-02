# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 12:25:57 by katakagi          #+#    #+#              #
#    Updated: 2023/02/02 10:45:48 by susami           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC		= cc
SRC_DIR	= src
SRCS	=	$(SRC_DIR)/main.c\
			$(SRC_DIR)/vec.c\
			$(SRC_DIR)/color.c\
			$(SRC_DIR)/utils.c\
			$(SRC_DIR)/parse.c\
			$(SRC_DIR)/error.c\
			$(SRC_DIR)/img.c\
			$(SRC_DIR)/hooks.c\
			$(SRC_DIR)/sphere.c\
			$(SRC_DIR)/ray_trace.c\

DEBUG_SRCS	= $(SRC_DIR)/destructor.c
DEBUG_OBJS	= $(DEBUG_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = obj
OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX_DIR	= minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a

INCLUDE		= -I $(MLX_DIR) -I /usr/X11R6/include -I $(SRC_DIR)

CFLAGS		= -Wall -Wextra -Werror $(INCLUDE)
DFLAGS		= -g -fsanitize=address -Weverything

FRAMEWORK	= -framework OpenGL -framework AppKit
LIBPATH		=-lmlx -lX11 -lXext	-L$(MLX_DIR) -L/usr/X11R6/lib

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(LIBPATH) $(FRAMEWORK) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@);
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUG_OBJS): $(DEBUG_SRCS)
	@mkdir -p $(dir $@);
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
	norminette $(SRC_DIR) | grep -E -v "TOO_MANY|TOO_LONG|WRONG_SCOPE_COMMENT"

test: SRCS += $(DEBUG_SRCS)
test: fclean $(DEBUG_OBJS) all $(OBJS)
	./test.sh

.PHONY: all clean fcelan re norm test
