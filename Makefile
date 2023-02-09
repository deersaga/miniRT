NAME	= miniRT

CC		= cc
SRC_DIR	= src
SRCS	=	$(SRC_DIR)/main.c\
			$(SRC_DIR)/vec.c\
			$(SRC_DIR)/vec_arith.c\
			$(SRC_DIR)/vec_utils.c\
			$(SRC_DIR)/element.c\
			$(SRC_DIR)/element_alloc_ACL.c\
			$(SRC_DIR)/element_alloc_other.c\
			$(SRC_DIR)/color.c\
			$(SRC_DIR)/utils.c\
			$(SRC_DIR)/parse.c\
			$(SRC_DIR)/parse_ACL.c\
			$(SRC_DIR)/parse_other.c\
			$(SRC_DIR)/parse_expect.c\
			$(SRC_DIR)/parse_validate_utils.c\
			$(SRC_DIR)/error.c\
			$(SRC_DIR)/img.c\
			$(SRC_DIR)/hooks.c\
			$(SRC_DIR)/sphere.c\
			$(SRC_DIR)/plane.c\
			$(SRC_DIR)/cylinder.c\
			$(SRC_DIR)/ray_trace.c\
			$(SRC_DIR)/translate1.c\
			$(SRC_DIR)/translate2.c\
			$(SRC_DIR)/hittable.c\
			$(SRC_DIR)/hittable_list.c\
			$(SRC_DIR)/tokenize.c\
			$(SRC_DIR)/tokenize_is.c\
			$(SRC_DIR)/tokenize_consume.c\
			$(SRC_DIR)/testcode.c\

DEBUG_SRCS	= $(SRC_DIR)/destructor.c\
			  $(SRC_DIR)/debug.c
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
	norminette $(SRC_DIR) | grep -E -v "WRONG_SCOPE_COMMENT|TOO_MANY_FUNCS|TOO_MANY_LINES|TOO_MANY_VARS_FUNC|TOO_MANY_ARGS"

test: SRCS += $(DEBUG_SRCS)
test: fclean $(DEBUG_OBJS) all $(OBJS)
	./test.sh

.PHONY: all clean fcelan re norm test
