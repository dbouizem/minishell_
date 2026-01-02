NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
INCLUDES = -I./includes -I./libft

READLINE_DIR := $(shell brew --prefix readline)
CFLAGS += -I$(READLINE_DIR)/include
LDFLAGS += -L$(READLINE_DIR)/lib -lreadline

RM = rm -rf

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

SRC =	$(SRC_DIR)/main.c \
		\
		$(SRC_DIR)/core/input.c \
		$(SRC_DIR)/core/shell.c \
		$(SRC_DIR)/core/processor.c \
		$(SRC_DIR)/core/shell_errors.c \
		$(SRC_DIR)/core/signals.c \
		\
		$(SRC_DIR)/lexer/tokenize.c \
		$(SRC_DIR)/lexer/token_utils.c \
		$(SRC_DIR)/lexer/lexer_checks.c \
		$(SRC_DIR)/lexer/lexer_handlers.c \
		$(SRC_DIR)/lexer/lexer_word_utils.c \
		$(SRC_DIR)/lexer/lexer_redir.c \
		$(SRC_DIR)/lexer/lexer_errors.c \
		\
		$(SRC_DIR)/parser/parse.c \
		$(SRC_DIR)/parser/parse_cmd.c \
		$(SRC_DIR)/parser/parse_args.c \
		$(SRC_DIR)/parser/parse_redir.c \
		$(SRC_DIR)/parser/parse_utils.c \
		$(SRC_DIR)/parser/parse_cleanup.c \
		$(SRC_DIR)/parser/parse_syntax.c \
		$(SRC_DIR)/parser/parse_errors.c \
		\
		$(SRC_DIR)/expander/expand.c \
		$(SRC_DIR)/expander/expand_quotes.c \
		$(SRC_DIR)/expander/expand_utils.c \
		$(SRC_DIR)/expander/expand_string.c \
		$(SRC_DIR)/expander/process_dollar.c \
		$(SRC_DIR)/expander/dollar_utils.c \
		$(SRC_DIR)/expander/process_normal.c \
		$(SRC_DIR)/expander/remove_quotes_final.c \
		\
		$(SRC_DIR)/executor/executor.c \
		$(SRC_DIR)/executor/pipeline.c \
		$(SRC_DIR)/executor/pipeline_utils.c \
		$(SRC_DIR)/executor/external.c \
		$(SRC_DIR)/executor/external_utils.c \
		$(SRC_DIR)/executor/redirections.c \
		$(SRC_DIR)/executor/redirections_utils.c \
		$(SRC_DIR)/executor/exec_errors.c \
		$(SRC_DIR)/executor/heredoc.c \
		$(SRC_DIR)/executor/heredoc_utils.c \
		$(SRC_DIR)/executor/child_executor.c \
		\
		$(SRC_DIR)/builtin/builtin.c \
		$(SRC_DIR)/builtin/builtin_echo.c \
		$(SRC_DIR)/builtin/builtin_exit.c \
		$(SRC_DIR)/builtin/builtin_pwd.c \
		$(SRC_DIR)/builtin/builtin_cd.c \
		$(SRC_DIR)/builtin/builtin_env.c \
		$(SRC_DIR)/builtin/builtin_export.c \
		$(SRC_DIR)/builtin/builtin_unset.c \
		\
		$(SRC_DIR)/env/env_array.c \
		$(SRC_DIR)/env/env_list.c \
		$(SRC_DIR)/env/env_utils.c \
		$(SRC_DIR)/env/env_errors.c \
		\
		$(SRC_DIR)/debug/debug_env.c \
		$(SRC_DIR)/debug/debug_parse.c \
		$(SRC_DIR)/debug/debug_executor.c \
		$(SRC_DIR)/debug/debug_lexer.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

BONUS_DIR = src_bonus

REPLACED_SRC = $(SRC_DIR)/lexer/lexer_redir.c \
			   $(SRC_DIR)/parser/parse.c \
			   $(SRC_DIR)/parser/parse_cmd.c \
			   $(SRC_DIR)/executor/executor.c

BONUS_SRC =	src_bonus/lexer/lexer_op_bonus.c \
			src_bonus/lexer/lexer_redir_bonus.c \
			src_bonus/parser/parse_bonus.c \
			src_bonus/parser/parse_cmd_bonus.c \
			src_bonus/executor/executor_bonus.c

SRC_FOR_BONUS = $(filter-out $(REPLACED_SRC), $(SRC))
OBJ_FOR_BONUS = $(SRC_FOR_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS_SRC:src_bonus/%.c=$(OBJ_DIR)/%.o)

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

$(OBJ_DIR)/%.o: src_bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(LIBFT_LIB) $(OBJ_FOR_BONUS) $(BONUS_OBJ)
	@echo "$(BOLD)$(YELLOW)🎁 Building Minishell with BONUS features...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ_FOR_BONUS) $(BONUS_OBJ) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Minishell BONUS built successfully!$(NC)"

bclean :
	@$(RM) $(BONUS_OBJ)
	@echo "$(YELLOW)🧹 Bonus object files removed$(NC)"
	@$(MAKE) --no-print-directory $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)🧹 Object files removed$(NC)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)🧹 Executable removed$(NC)"

re: fclean all

.PHONY: all bonus clean fclean re bclean
