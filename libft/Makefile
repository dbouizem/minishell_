NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Couleurs pour les messages
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m
BOLD = \033[1m

OBJ_DIR = objs

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
	get_next_line.c \
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
	ft_free_tab.c

SRCS_BONUS =	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJ_DIR)/%.o)

TOTAL_SRCS = $(words $(SRCS))
TOTAL_BONUS = $(words $(SRCS_BONUS))

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "$(BOLD)$(GREEN)🔨 [LIBFT] Création de la bibliothèque $(NAME)...$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@echo "$(BOLD)$(GREEN)✅ [LIBFT] $(NAME) créée avec succès! ($(TOTAL_SRCS) fonctions)$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)📁 [LIBFT] Compilation de $(notdir $<)...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✓ [LIBFT] $(notdir $<) → $(notdir $@)$(RESET)"

bonus : $(OBJS) $(OBJS_BONUS)
	@echo "$(BOLD)$(YELLOW)🎯 [LIBFT] Création de la bibliothèque avec bonus...$(RESET)"
	@ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	@echo "$(BOLD)$(GREEN)✅ [LIBFT] $(NAME) avec bonus créée! ($(TOTAL_SRCS) + $(TOTAL_BONUS) fonctions)$(RESET)"

clean :
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(YELLOW)🧹 [LIBFT] Nettoyage des fichiers objets...$(RESET)"; \
		rm -rf $(OBJ_DIR) $(OBJS) $(OBJS_BONUS); \
		echo "$(GREEN)✓ [LIBFT] Fichiers objets supprimés$(RESET)"; \
	else \
		echo "$(BLUE)ℹ️  [LIBFT] Aucun fichier objet à nettoyer$(RESET)"; \
	fi

fclean : clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(YELLOW)🗑️  [LIBFT] Suppression de $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(GREEN)✓ [LIBFT] $(NAME) supprimée$(RESET)"; \
	else \
		echo "$(BLUE)ℹ️  [LIBFT] $(NAME) déjà supprimée$(RESET)"; \
	fi

re : fclean all

rebonus : fclean bonus

.PHONY : clean fclean re all bonus rebonus
