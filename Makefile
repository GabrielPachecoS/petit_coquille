# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:08:24 by gapachec          #+#    #+#              #
#    Updated: 2025/08/28 17:48:40 by jucoelho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= minishell
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBFT_DIR	= libft

SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/debug.c \
		  $(SRC_DIR)/cleanup.c \
		  $(SRC_DIR)/signals.c \
		  $(SRC_DIR)/start_minishell.c \
		  $(SRC_DIR)/lexer/00lexer.c \
		  $(SRC_DIR)/lexer/01lexer_handle.c \
		  $(SRC_DIR)/lexer/02lexer_tokens.c \
		  $(SRC_DIR)/lexer/03lexer_utils.c \
		  $(SRC_DIR)/parser/00parser.c \
		  $(SRC_DIR)/parser/01parser_redir.c \
		  $(SRC_DIR)/parser/02parser_utils.c \
		  $(SRC_DIR)/parser/03parser_free.c \
		  $(SRC_DIR)/expander/00expander.c \
		  $(SRC_DIR)/expander/01exp_squot.c \
		  $(SRC_DIR)/expander/02exp_dquot.c \
		  $(SRC_DIR)/expander/03exp_quot.c \
		  $(SRC_DIR)/expander/04exp_handle.c \
		  $(SRC_DIR)/expander/05exp_utils.c \
		  $(SRC_DIR)/exec/00exec_cmd.c \
		  $(SRC_DIR)/exec/01exec.c \
		  $(SRC_DIR)/exec/02exec_redir.c \
		  $(SRC_DIR)/exec/03exec_redir.c \
		  $(SRC_DIR)/exec/04exec_path.c \
		  $(SRC_DIR)/exec/05exec_free_error.c \
		  $(SRC_DIR)/env/00env_init.c \
		  $(SRC_DIR)/env/01env_to_array.c \
		  $(SRC_DIR)/env/02env_set_unset.c \
		  $(SRC_DIR)/env/03env_print.c \
		  $(SRC_DIR)/env/04env_utils.c \
		  $(SRC_DIR)/env/05env_free.c \
		  $(SRC_DIR)/builtin/00builtin.c \
		  $(SRC_DIR)/builtin/01builtin_echo.c \
		  $(SRC_DIR)/builtin/02builtin_cd.c \
		  $(SRC_DIR)/builtin/03builtin_pwd.c \
		  $(SRC_DIR)/builtin/04builtin_export.c \
		  $(SRC_DIR)/builtin/05builtin_unset.c \
		  $(SRC_DIR)/builtin/06builtin_env.c \
		  $(SRC_DIR)/builtin/07builtin_exit.c 

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INC		= -I$(INC_DIR) -I$(LIBFT_DIR)
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(LIBFT_DIR)/libft.a $(NAME)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@echo "🔗 Ligando $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) -lreadline
	@echo "\033[1;45m✅ Petit Coquile 🥟 compilado com sucesso!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "🛠️  Compilando $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

run: all
	valgrind --suppressions=readline.sup --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell
	
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
re: fclean all

.PHONY: all clean fclean re
-include $(DEP)
