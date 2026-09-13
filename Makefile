NAME		= life

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
IFLAGS		= -Iincludes -Ilibft -Iminilibx

INC_DIR		= includes
SRC_DIR		= srcs
OBJ_DIR		= obj
LIBFT_DIR	= libft
MLX_DIR		= minilibx

SRCS		= main.c \
			  error.c \
			  parse_args.c \
			  parse_config.c \
			  parse_config_keys.c \
			  parse_pattern.c \
			  parse_rule.c \
			  parse_random.c \
			  grid_alloc.c \
			  grid_utils.c \
			  rules_step.c \
			  init_mlx.c \
			  render.c \
			  hooks_key.c \
			  hooks_loop.c \
			  cleanup.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

MLX_LIB		= $(MLX_DIR)/libmlx.a
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
LIBS		= -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lbsd -lm

all: $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/life.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
