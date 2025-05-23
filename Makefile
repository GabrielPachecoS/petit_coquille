# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:08:24 by gapachec          #+#    #+#              #
#    Updated: 2025/05/23 17:43:22 by jucoelho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBFT_DIR	= libft

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INC		= -I$(INC_DIR) -I$(LIBFT_DIR)

SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/start_minishell.c \
		  $(SRC_DIR)/signals.c \
		  $(SRC_DIR)/cleanup.c \
		  $(SRC_DIR)/exec.c \
		  $(SRC_DIR)/path.c \
		  $(SRC_DIR)/lexer/lexer.c \
		  $(SRC_DIR)/lexer/lexer_utils.c \
		  $(SRC_DIR)/parser/parser.c \
		  $(SRC_DIR)/parser/parser_utils.c

# Geração automática dos .o a partir dos .c
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Instrução para incluir dependências (geradas com -MMD)
DEP		= $(OBJ:.o=.d)

all: $(LIBFT_DIR) $(OBJ_DIR) $(OBJ_DIR)/lexer $(OBJ_DIR)/parser $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR)/lexer/%.o: $(SRC_DIR)/lexer/%.c | $(OBJ_DIR)/lexer
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR)/parser/%.o: $(SRC_DIR)/parser/%.c | $(OBJ_DIR)/parser
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/lexer:
	mkdir -p $(OBJ_DIR)/lexer

$(OBJ_DIR)/parser:
	mkdir -p $(OBJ_DIR)/parser

clean:
	rm -rf $(OBJ_DIR)

# Limpa tudo (inclusive o binário)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
-include $(DEP)
