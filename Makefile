NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_BONUS	= -DBONUS
INCLUDES	= -I./includes -I./libft/includes

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	READLINE_DIR := $(shell brew --prefix readline 2>/dev/null)
	ifneq ($(READLINE_DIR),)
		CFLAGS  += -I$(READLINE_DIR)/include
		LDFLAGS += -L$(READLINE_DIR)/lib
	endif
	LDFLAGS += -lreadline
else
	READLINE_LIBS := $(shell pkg-config --libs readline 2>/dev/null)
	ifneq ($(READLINE_LIBS),)
		LDFLAGS += $(READLINE_LIBS)
	else
		LDFLAGS += -lreadline -lncurses
		ifneq ($(wildcard /usr/lib*/libtinfo.so* /lib*/libtinfo.so*),)
			LDFLAGS += -ltinfo
		endif
	endif
endif

SRC_DIR		= srcs
SRC_BONUS_DIR	= srcs_bonus
OBJ_DIR		= obj
OBJ_DIR_BONUS	= obj_bonus
INC_DIR		= includes
LIBFT_DIR	= libft

SRC_BASE =	$(SRC_DIR)/main.c \
		\
		$(SRC_DIR)/core/input.c \
		$(SRC_DIR)/core/shell.c \
		$(SRC_DIR)/core/shell_level.c \
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
		$(SRC_DIR)/executor/core/executor.c \
		$(SRC_DIR)/executor/core/command_exec.c \
		$(SRC_DIR)/executor/core/child_executor.c \
		$(SRC_DIR)/executor/pipeline/pipeline_exec.c \
		$(SRC_DIR)/executor/pipeline/pipeline_create.c \
		$(SRC_DIR)/executor/pipeline/pipeline_fork.c \
		$(SRC_DIR)/executor/pipeline/pipeline_wait.c \
		$(SRC_DIR)/executor/pipeline/pipeline_heredoc.c \
		$(SRC_DIR)/executor/external/external_exec.c \
		$(SRC_DIR)/executor/external/path_search.c \
		$(SRC_DIR)/executor/utils/exec_utils.c \
		$(SRC_DIR)/executor/utils/exec_wait.c \
		$(SRC_DIR)/executor/utils/exec_signal_status.c \
		$(SRC_DIR)/executor/utils/exec_errors.c \
		$(SRC_DIR)/executor/redirections/redirections_core.c \
		$(SRC_DIR)/executor/redirections/redirections_state.c \
		$(SRC_DIR)/executor/redirections/redirections_utils.c \
		$(SRC_DIR)/executor/heredoc/heredoc_core.c \
		$(SRC_DIR)/executor/heredoc/heredoc_tmp.c \
		$(SRC_DIR)/executor/heredoc/heredoc_expand.c \
		$(SRC_DIR)/executor/heredoc/heredoc_content.c \
		$(SRC_DIR)/executor/heredoc/heredoc_read.c \
		$(SRC_DIR)/executor/heredoc/heredoc_utils.c \
		\
		$(SRC_DIR)/builtin/builtin.c \
		$(SRC_DIR)/builtin/builtin_echo.c \
		$(SRC_DIR)/builtin/builtin_exit.c \
		$(SRC_DIR)/builtin/builtin_pwd.c \
		$(SRC_DIR)/builtin/builtin_cd.c \
		$(SRC_DIR)/builtin/builtin_env.c \
		$(SRC_DIR)/builtin/builtin_env_assign.c \
		$(SRC_DIR)/builtin/builtin_export.c \
		$(SRC_DIR)/builtin/builtin_export_print.c \
		$(SRC_DIR)/builtin/builtin_unset.c \
		$(SRC_DIR)/builtin/errors_builtin.c \
		\
		$(SRC_DIR)/env/env_array.c \
		$(SRC_DIR)/env/env_list.c \
		$(SRC_DIR)/env/env_list_dup.c \
		$(SRC_DIR)/env/env_list_utils.c \
		$(SRC_DIR)/env/env_utils.c \
		$(SRC_DIR)/env/env_unset.c \
		$(SRC_DIR)/env/env_errors.c \
		$(SRC_DIR)/env/env_minimal.c

SRC_BONUS_BASE =	$(filter-out \
		$(SRC_DIR)/core/processor.c \
		$(SRC_DIR)/lexer/lexer_redir.c \
		$(SRC_DIR)/lexer/lexer_checks.c \
		$(SRC_DIR)/executor/core/executor.c \
		$(SRC_DIR)/executor/core/command_exec.c, \
		$(SRC_BASE))

SRC_BONUS_ONLY =\
	$(SRC_BONUS_DIR)/lexer/lexer_redir_bonus.c \
	$(SRC_BONUS_DIR)/lexer/lexer_checks_bonus.c \
	$(SRC_BONUS_DIR)/lexer/lexer_op_bonus.c \
	$(SRC_BONUS_DIR)/core/processor_bonus.c \
	$(SRC_BONUS_DIR)/parser/parse_ast_bonus.c \
	$(SRC_BONUS_DIR)/parser/parse_ast_bonus_pipeline.c \
	$(SRC_BONUS_DIR)/parser/parse_ast_bonus_logical.c \
	$(SRC_BONUS_DIR)/expander/wildcard_pattern_bonus.c \
	$(SRC_BONUS_DIR)/expander/wildcard_expand_bonus.c \
	$(SRC_BONUS_DIR)/expander/wildcard_utils_bonus.c \
	$(SRC_BONUS_DIR)/executor/executor_bonus.c \
	$(SRC_BONUS_DIR)/executor/exec_ast_bonus.c

SRC_BONUS =	$(SRC_BONUS_BASE) $(SRC_BONUS_ONLY)
SRC =	$(SRC_BASE)

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_BONUS	= $(SRC_BONUS_BASE:$(SRC_DIR)/%.c=$(OBJ_DIR_BONUS)/%.o) \
		$(SRC_BONUS_ONLY:$(SRC_BONUS_DIR)/%.c=$(OBJ_DIR_BONUS)/bonus/%.o)

LIBFT_HEADERS	= $(wildcard $(LIBFT_DIR)/*.h)
HEADERS		= $(wildcard $(INC_DIR)/*.h) $(LIBFT_HEADERS)
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft
BONUS_STAMP	= $(OBJ_DIR_BONUS)/.bonus

BOLD   = \033[1m
CYAN   = \033[0;36m
GREEN  = \033[0;32m
RED    = \033[0;31m
BLUE   = \033[0;34m
YELLOW = \033[0;33m
RESET  = \033[0m

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJ) $(LIBFT_LIB)
	@echo "$(BOLD)$(CYAN)🔗 Linking minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(BOLD)$(GREEN)✅ Minishell ready!$(RESET)\n"

bonus: $(BONUS_STAMP)

$(BONUS_STAMP): $(LIBFT_LIB) $(OBJ_BONUS)
	@echo "$(BOLD)$(CYAN)🔗 Linking minishell (bonus)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)
	@touch $(BONUS_STAMP)
	@echo "$(BOLD)$(GREEN)✅ Minishell bonus ready!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CFLAGS_BONUS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_BONUS)/bonus/%.o: $(SRC_BONUS_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CFLAGS_BONUS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(BOLD)$(CYAN)🧹 Cleaning minishell objects...$(RESET)"; \
		rm -rf $(OBJ_DIR); \
		echo "$(GREEN)✓ Minishell cleaned$(RESET)"; \
	fi
	@if [ -d "$(OBJ_DIR_BONUS)" ]; then \
		echo "$(BOLD)$(CYAN)🧹 Cleaning minishell bonus objects...$(RESET)"; \
		rm -rf $(OBJ_DIR_BONUS); \
		echo "$(GREEN)✓ Minishell bonus cleaned$(RESET)"; \
	fi

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@if [ -f "$(NAME)" ]; then \
		echo "$(BOLD)$(CYAN)🗑️  Removing minishell...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(GREEN)✓ Minishell removed$(RESET)"; \
	fi

re: fclean all
re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
