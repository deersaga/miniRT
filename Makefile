NAME	= miniRT

CC		= cc
SRCS		= main.c

OBJ_DIR = ./obj
OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)

CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -g -fsanitize=address -Weverything
FRAMEWORK = -framework OpenGL -framework AppKit

$(NAME): $(OBJS)
	$(CC) $(FRAMEWORK) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@);
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS)

fclean:
	rm $(NAME) $(OBJS)

all: $(NAME)

re: fclean all

norm:
	norminette $(SRCS)

.PHONY: all clean fcelan re norm