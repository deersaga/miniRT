NAME	= miniRT

CC		= cc
SRC_DIR	= src
SRCS	=	$(SRC_DIR)/main.c\
			$(SRC_DIR)/vec/vec.c\
			$(SRC_DIR)/vec/vec_arith.c\
			$(SRC_DIR)/vec/vec_utils.c\
			$(SRC_DIR)/parse/element.c\
			$(SRC_DIR)/parse/element_alloc_ACL.c\
			$(SRC_DIR)/parse/element_alloc_other.c\
			$(SRC_DIR)/parse/element_validate.c\
			$(SRC_DIR)/parse/element_validate_utils1.c\
			$(SRC_DIR)/parse/element_validate_utils2.c\
			$(SRC_DIR)/parse/parse.c\
			$(SRC_DIR)/parse/parse_ACL.c\
			$(SRC_DIR)/parse/parse_other.c\
			$(SRC_DIR)/parse/parse_expect_token.c\
			$(SRC_DIR)/parse/tokenize.c\
			$(SRC_DIR)/parse/tokenize_is.c\
			$(SRC_DIR)/parse/tokenize_consume.c\
			$(SRC_DIR)/parse/translate1.c\
			$(SRC_DIR)/parse/translate2.c\
			$(SRC_DIR)/hittable/sphere.c\
			$(SRC_DIR)/hittable/plane.c\
			$(SRC_DIR)/hittable/cylinder.c\
			$(SRC_DIR)/hittable/hittable.c\
			$(SRC_DIR)/hittable/hittable_list.c\
			$(SRC_DIR)/utils/ft_strtod.c\
			$(SRC_DIR)/utils/error.c\
			$(SRC_DIR)/utils/get_mlx_color.c\
			$(SRC_DIR)/utils/range.c\
			$(SRC_DIR)/utils/degrees_to_radians.c\
			$(SRC_DIR)/utils/img.c\
			$(SRC_DIR)/hooks.c\
			$(SRC_DIR)/ray_trace.c\
			$(SRC_DIR)/ray.c\

DEBUG_SRCS	= $(SRC_DIR)/debug.c

DEBUG_OBJS	= $(DEBUG_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = obj
OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX_DIR	= minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_DIRS := $(shell find $(SRC_DIR) -type d -print)
INCLUDE		=	-I $(MLX_DIR) \
				-I /usr/X11R6/include \
				-I $(SRC_DIR) \
				-I $(LIBFT_DIR) \
				$(addprefix -I ,$(SRC_DIRS))

CFLAGS		= -Wall -Wextra -Werror $(INCLUDE)
DFLAGS		= -g -fsanitize=address -Weverything
FRAMEWORK	= -framework OpenGL -framework AppKit
LIBPATH		=-lmlx -lX11 -lXext	-lft -L$(LIBFT_DIR) -L$(MLX_DIR) -L/usr/X11R6/lib

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(LIBPATH) $(FRAMEWORK) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@);
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(DEBUG_OBJS): $(DEBUG_SRCS)
	@mkdir -p $(dir $@);
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

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
