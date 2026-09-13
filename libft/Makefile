NAME	= libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iincludes -Ift_printf -Ignl
AR		= ar rcs
OBJ_DIR	= obj

SRCS	= srcs/ft_isalnum.c \
		  srcs/ft_isalpha.c \
		  srcs/ft_isascii.c \
		  srcs/ft_isdigit.c \
		  srcs/ft_isprint.c \
		  srcs/ft_isspace.c \
		  srcs/ft_tolower.c \
		  srcs/ft_toupper.c \
		  srcs/ft_bzero.c \
		  srcs/ft_memset.c \
		  srcs/ft_memcpy.c \
		  srcs/ft_memmove.c \
		  srcs/ft_memchr.c \
		  srcs/ft_memcmp.c \
		  srcs/ft_calloc.c \
		  srcs/ft_strlen.c \
		  srcs/ft_strcmp.c \
		  srcs/ft_strncmp.c \
		  srcs/ft_strlcpy.c \
		  srcs/ft_strlcat.c \
		  srcs/ft_strdup.c \
		  srcs/ft_strnstr.c \
		  srcs/ft_strrchr.c \
		  srcs/ft_strchr.c \
		  srcs/ft_substr.c \
		  srcs/ft_strjoin.c \
		  srcs/ft_strtrim.c \
		  srcs/ft_split.c \
		  srcs/ft_free_split.c \
		  srcs/ft_strmapi.c \
		  srcs/ft_striteri.c \
		  srcs/ft_strreplace.c \
		  srcs/ft_atoi.c \
		  srcs/ft_valid_int.c \
		  srcs/ft_itoa.c \
		  srcs/ft_itoa_base.c \
		  srcs/ft_utoa_base.c \
		  srcs/ft_putchar_fd.c \
		  srcs/ft_putstr_fd.c \
		  srcs/ft_putendl_fd.c \
		  srcs/ft_putnbr_fd.c \
		  srcs/ft_read_file.c \
		  srcs/ft_lstnew.c \
		  srcs/ft_lstadd_front.c \
		  srcs/ft_lstadd_back.c \
		  srcs/ft_lstsize.c \
		  srcs/ft_lstlast.c \
		  srcs/ft_lstdelone.c \
		  srcs/ft_lstclear.c \
		  srcs/ft_lstiter.c \
		  srcs/ft_lstmap.c \
		  srcs/ft_lstclone.c \
		  srcs/ft_printf.c \
		  ft_printf/ft_dispatch_format.c \
		  ft_printf/ft_is_valid_base.c \
		  ft_printf/ft_putnchar.c \
		  ft_printf/ft_parse_format.c \
		  ft_printf/ft_parse_decimal.c \
		  ft_printf/ft_parse_unsigned.c \
		  ft_printf/ft_parse_char.c \
		  ft_printf/ft_parse_string.c \
		  srcs/get_next_line.c \
		  gnl/get_next_line_utils.c

HDRS	= includes/libft.h ft_printf/ft_printf.h ft_printf/ft_printf_utils.h \
		  gnl/get_next_line.h

OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
