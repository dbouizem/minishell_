# PROJECT
NAME	=libft.a

# COMPILER & FLAGS
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iincludes

# DIRECTORIES & FILES
OBJ_DIR	= objs
HEADERS	= includes/libft.h

# SOURCES
SRCS_CTYPE =	src/ctype/ft_isalpha.c \
				src/ctype/ft_isdigit.c \
				src/ctype/ft_isalnum.c \
				src/ctype/ft_isascii.c \
				src/ctype/ft_isprint.c \
				src/ctype/ft_isspace.c \
				src/ctype/ft_tolower.c \
				src/ctype/ft_toupper.c \
				src/ctype/ft_isnumber.c

SRCS_STRING =	src/string/ft_strlen.c \
				src/string/ft_strlcpy.c \
				src/string/ft_strlcat.c \
				src/string/ft_strchr.c \
				src/string/ft_strrchr.c \
				src/string/ft_strnstr.c \
				src/string/ft_strdup.c \
				src/string/ft_strncmp.c \
				src/string/ft_strcmp.c \
				src/string/ft_striteri.c \
				src/string/ft_strmapi.c \
				src/string/ft_strjoin.c \
				src/string/ft_strjoin3.c \
				src/string/ft_strtrim.c \
				src/string/ft_split.c \
				src/string/ft_substr.c \
				src/string/ft_strncpy.c \
				src/string/ft_strstr.c

SRCS_STDLIB =	src/stdlib/ft_memset.c \
				src/stdlib/ft_bzero.c \
				src/stdlib/ft_memcpy.c \
				src/stdlib/ft_memmove.c \
				src/stdlib/ft_memchr.c \
				src/stdlib/ft_memcmp.c \
				src/stdlib/ft_calloc.c \
				src/stdlib/ft_atoi.c \
				src/stdlib/ft_atoll.c \
				src/stdlib/ft_itoa.c \
				src/stdlib/ft_free_tab.c

SRCS_IO =		src/io/ft_putchar_fd.c \
				src/io/ft_putstr_fd.c \
				src/io/ft_putendl_fd.c \
				src/io/ft_putnbr_fd.c

SRCS_PRINTF =	src/printf/ft_printf.c \
				src/printf/parse_format.c \
				src/printf/ft_print_char.c \
				src/printf/ft_print_str.c \
				src/printf/ft_print_ptr.c \
				src/printf/ft_print_int.c \
				src/printf/ft_print_u_int.c \
				src/printf/ft_print_hex.c

SRCS_GNL =		src/gnl/ft_gnl.c \
				src/gnl/ft_gnl_clear.c

SRCS = $(SRCS_CTYPE) $(SRCS_STRING) $(SRCS_STDLIB) $(SRCS_IO) $(SRCS_PRINTF) $(SRCS_GNL)

SRCS_BONUS =	src/list/ft_lstnew.c \
				src/list/ft_lstadd_front.c \
				src/list/ft_lstsize.c \
				src/list/ft_lstlast.c \
				src/list/ft_lstadd_back.c \
				src/list/ft_lstdelone.c \
				src/list/ft_lstclear.c \
				src/list/ft_lstiter.c \
				src/list/ft_lstmap.c

# OBJECTS
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS	= $(SRCS_BONUS:%.c=$(OBJ_DIR)/%.o)

# COLORS - LIBFT (Magenta/Purple)
MAGENTA	= \033[0;35m
PURPLE	= \033[0;95m
GREEN	= \033[0;32m
RED		= \033[0;31m
BOLD	= \033[1m
RESET	= \033[0m

# RULES
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(BOLD)$(GREEN)✅ Libft ready$(RESET)"

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(OBJS_BONUS)
	@ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	@echo "$(BOLD)$(GREEN)✅ Libft (bonus) ready$(RESET)"

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(BOLD)$(MAGENTA)🧹 Cleaning libft objects...$(RESET)"; \
		rm -rf $(OBJ_DIR); \
		echo "$(GREEN)✓ Libft cleaned$(RESET)"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(BOLD)$(MAGENTA)🗑️  Removing libft.a...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(GREEN)✓ Libft removed$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re bonus
