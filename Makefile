# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:08:24 by gapachec          #+#    #+#              #
#    Updated: 2025/07/18 20:15:42 by gapachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= minishell
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBFT_DIR	= libft

SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/start_minishell.c \
		  $(SRC_DIR)/signals.c \
		  $(SRC_DIR)/cleanup.c \
		  $(SRC_DIR)/debug.c \
		  $(SRC_DIR)/exec/00exec.c \
		  $(SRC_DIR)/exec/02exec.c \
		  $(SRC_DIR)/exec/04path.c \
		  $(SRC_DIR)/lexer/lexer.c \
		  $(SRC_DIR)/lexer/lexer_utils.c \
		  $(SRC_DIR)/lexer/lexer_tokens.c \
		  $(SRC_DIR)/lexer/lexer_handle.c \
		  $(SRC_DIR)/parser/parser.c \
		  $(SRC_DIR)/parser/parser_utils.c \
		  $(SRC_DIR)/env/env_free.c \
		  $(SRC_DIR)/env/env_init.c \
		  $(SRC_DIR)/env/env_utils.c \
		  $(SRC_DIR)/env/env_print.c \
		  $(SRC_DIR)/env/env_set_unset.c \
		  $(SRC_DIR)/env/env_to_array.c \
		  $(SRC_DIR)/builtin/builtin_cd.c \
		  $(SRC_DIR)/builtin/builtin_echo.c \
		  $(SRC_DIR)/builtin/builtin_env.c \
		  $(SRC_DIR)/builtin/builtin_exit.c \
		  $(SRC_DIR)/builtin/builtin_export.c \
		  $(SRC_DIR)/builtin/builtin_pwd.c \
		  $(SRC_DIR)/builtin/builtin_unset.c \
		  $(SRC_DIR)/builtin/builtin.c \




CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INC		= -I$(INC_DIR) -I$(LIBFT_DIR)

# Geração automática dos .o a partir dos .c
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Instrução para incluir dependências (geradas com -MMD)
DEP		= $(OBJ:.o=.d)

all: $(LIBFT_DIR)/libft.a $(OBJ_DIR) $(OBJ_DIR)/lexer \
	$(OBJ_DIR)/parser $(OBJ_DIR)/env $(OBJ_DIR)/builtin $(NAME)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# Tirar regra de compilação antes de enviarrrrrrr!!!
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) -lreadline
	@echo "\033[1;45m✅ Petit Coquile compiled successfully!!\033[0m"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR)/exec/%.o: $(SRC_DIR)/exec/%.c | $(OBJ_DIR)/exec
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR)/lexer/%.o: $(SRC_DIR)/lexer/%.c | $(OBJ_DIR)/lexer
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR)/parser/%.o: $(SRC_DIR)/parser/%.c | $(OBJ_DIR)/parser
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR)/env/%.o: $(SRC_DIR)/env/%.c | $(OBJ_DIR)/env
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR)/builtin/%.o: $(SRC_DIR)/builtin/%.c | $(OBJ_DIR)/builtin
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/exec:
	mkdir -p $(OBJ_DIR)/exec

$(OBJ_DIR)/lexer:
	mkdir -p $(OBJ_DIR)/lexer

$(OBJ_DIR)/parser:
	mkdir -p $(OBJ_DIR)/parser

$(OBJ_DIR)/env:
	mkdir -p $(OBJ_DIR)/env

$(OBJ_DIR)/builtin:
	mkdir -p $(OBJ_DIR)/builtin

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
re: fclean all

.PHONY: all clean fclean re
-include $(DEP)
