NAME	= libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I. -Ift_printf -Ignl
AR		= ar rcs
OBJ_DIR	= obj

SRCS	= ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_isspace.c \
		  ft_tolower.c \
		  ft_toupper.c \
		  ft_bzero.c \
		  ft_memset.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_calloc.c \
		  ft_strlen.c \
		  ft_strcmp.c \
		  ft_strncmp.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_strdup.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strchr.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_free_split.c \
		  ft_strmapi.c \
		  ft_striteri.c \
		  ft_strreplace.c \
		  ft_atoi.c \
		  ft_valid_int.c \
		  ft_itoa.c \
		  ft_itoa_base.c \
		  ft_utoa_base.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_read_file.c \
		  ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstadd_back.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c \
		  ft_lstclone.c \
		  ft_printf.c \
		  ft_printf/ft_dispatch_format.c \
		  ft_printf/ft_is_valid_base.c \
		  ft_printf/ft_putnchar.c \
		  ft_printf/ft_parse_format.c \
		  ft_printf/ft_parse_decimal.c \
		  ft_printf/ft_parse_unsigned.c \
		  ft_printf/ft_parse_char.c \
		  ft_printf/ft_parse_string.c \
		  get_next_line.c \
		  gnl/get_next_line_utils.c

HDRS	= libft.h ft_printf/ft_printf.h ft_printf/ft_printf_utils.h \
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
