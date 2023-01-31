# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 12:25:57 by katakagi          #+#    #+#              #
#    Updated: 2023/01/31 12:26:13 by katakagi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC		= cc
SRCS		= main.c

OBJ_DIR = ./obj
OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)

CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -g -fsanitize=address -Weverything

MLX_DIR	= minilibx-linux
FRAMEWORK = -lmlx -lX11 -lXext -framework OpenGL -framework AppKit
LIBPATH		=	-L$(MLX_DIR) -L/usr/X11R6/lib

$(NAME): $(OBJS)
	$(CC) $(LIBPATH) $(FRAMEWORK) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@);
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm $(OBJS)

fclean:
	rm $(NAME) $(OBJS)

all: $(NAME)

re: fclean all

norm:
	norminette $(SRCS) minirt.h

.PHONY: all clean fcelan re norm