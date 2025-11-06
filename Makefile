NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./libft

RM = rm -rf

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/core/input.c \
		$(SRC_DIR)/core/shell.c \
		$(SRC_DIR)/core/processor.c \
		$(SRC_DIR)/lexer/tokenize.c \
		$(SRC_DIR)/lexer/token_utils.c \
		$(SRC_DIR)/lexer/lexer_checks.c \
		$(SRC_DIR)/lexer/lexer_extract.c \
		$(SRC_DIR)/lexer/lexer_handlers.c \
		$(SRC_DIR)/lexer/lexer_redir.c \
		$(SRC_DIR)/parser/parse.c \
		$(SRC_DIR)/parser/parse_cmd.c \
		$(SRC_DIR)/parser/parse_args.c \
		$(SRC_DIR)/parser/parse_redir.c \
		$(SRC_DIR)/parser/parse_utils.c \
		$(SRC_DIR)/parser/parse_cleanup.c \
		$(SRC_DIR)/expander/expand.c \
		$(SRC_DIR)/expander/expand_var.c \
		$(SRC_DIR)/expander/expand_quotes.c \
		$(SRC_DIR)/expander/expand_utils.c \
		$(SRC_DIR)/expander/expand_string.c



OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# Couleurs complètes
BOLD = \033[1m
CYAN = \033[0;36m
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m
RESET = \033[0m

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@echo "$(BOLD)$(CYAN)🔧 Compilation de libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Libft compilée avec succès$(RESET)"

$(NAME): $(OBJ) $(LIBFT_LIB)
	@echo "$(BLUE)🔨 Building Minishell...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) -o $(NAME) -lreadline
	@echo "$(GREEN)✅ Minishell built successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)🧹 Object files removed$(NC)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)🧹 Executable removed$(NC)"

re: fclean all

.PHONY: all clean fclean re
