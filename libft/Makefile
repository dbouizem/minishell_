# PROJECT
NAME	=libft.a

# COMPILER & FLAGS
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

# DIRECTORIES & FILES
OBJ_DIR	= objs
HEADER	= libft.h

# SOURCES
SRCS =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_calloc.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strdup.c \
		ft_strncmp.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_striteri.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_split.c \
		ft_strncpy.c \
		ft_gnl.c \
		ft_printf.c \
		parse_format.c \
		ft_print_char.c \
		ft_print_str.c \
		ft_print_ptr.c \
		ft_print_int.c \
		ft_print_u_int.c \
		ft_print_hex.c \
		ft_strcmp.c \
		ft_strjoin3.c \
		ft_isnumber.c \
		ft_free_tab.c \
		ft_atoll.c

SRCS_BONUS =	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c

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

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
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
