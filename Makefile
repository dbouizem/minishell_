NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./libft

# --- Readline (Homebrew) Fix for macOS ---
READLINE_DIR := $(shell brew --prefix readline)
CFLAGS += -I$(READLINE_DIR)/include
LDFLAGS += -L$(READLINE_DIR)/lib -lreadline

RM = rm -rf

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/core/input.c \
		$(SRC_DIR)/core/shell.c \
		$(SRC_DIR)/core/processor.c \
		$(SRC_DIR)/core/signals.c \
		$(SRC_DIR)/lexer/tokenize.c \
		$(SRC_DIR)/lexer/token_utils.c \
		$(SRC_DIR)/lexer/lexer_checks.c \
		$(SRC_DIR)/lexer/lexer_handlers.c \
		$(SRC_DIR)/lexer/lexer_word_utils.c \
		$(SRC_DIR)/lexer/lexer_redir.c \
		$(SRC_DIR)/parser/parse.c \
		$(SRC_DIR)/parser/parse_cmd.c \
		$(SRC_DIR)/parser/parse_args.c \
		$(SRC_DIR)/parser/parse_redir.c \
		$(SRC_DIR)/parser/parse_utils.c \
		$(SRC_DIR)/parser/parse_cleanup.c \
		$(SRC_DIR)/parser/parse_syntax.c \
		$(SRC_DIR)/expander/expand.c \
		$(SRC_DIR)/expander/expand_var.c \
		$(SRC_DIR)/expander/expand_quotes.c \
		$(SRC_DIR)/expander/expand_utils.c \
		$(SRC_DIR)/expander/expand_string.c \
		$(SRC_DIR)/expander/process_dollar.c \
		$(SRC_DIR)/expander/process_normal.c \
		$(SRC_DIR)/execution/execute.c \
		$(SRC_DIR)/execution/execute_cmds.c \
		$(SRC_DIR)/builtin/builtin.c \
		$(SRC_DIR)/builtin/builtin_echo.c \
		$(SRC_DIR)/builtin/builtin_exit.c \
		$(SRC_DIR)/builtin/builtin_pwd.c \
		$(SRC_DIR)/builtin/builtin_env.c \
		$(SRC_DIR)/builtin/builtin_cd.c \
		$(SRC_DIR)/builtin/builtin_export.c \
		$(SRC_DIR)/builtin/builtin_unset.c \
		$(SRC_DIR)/builtin/env_utils.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# Colors
BOLD = \033[1m
CYAN = \033[0;36m
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@echo "$(BOLD)$(CYAN)🔧 Compilation de libft...$(NC)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Libft compilée avec succès$(NC)"

$(NAME): $(OBJ) $(LIBFT_LIB)
	@echo "$(BLUE)🔨 Building Minishell...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Minishell built successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
