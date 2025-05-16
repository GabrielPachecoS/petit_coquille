# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:08:24 by gapachec          #+#    #+#              #
#    Updated: 2025/05/16 12:07:21 by gapachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável final
NAME	= minishell

# Compilador e flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

# Diretórios
SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= include

# Lista de arquivos fonte (vai adicionando os outros aqui)
SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/start_minishell.c \
		  $(SRC_DIR)/signals.c \
		  $(SRC_DIR)/cleanup.c \
		  $(SRC_DIR)/lexer/lexer.c \
		  $(SRC_DIR)/lexer/utils.c \
		  $(SRC_DIR)/parser/parser.c

# Geração automática dos .o a partir dos .c
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Instrução para incluir dependências (geradas com -MMD)
DEP		= $(OBJ:.o=.d)

all: $(OBJ_DIR) $(OBJ_DIR)/lexer $(OBJ_DIR)/parser $(NAME)

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


# Limpa os arquivos objetos
clean:
	rm -rf $(OBJ_DIR)

# Limpa tudo (inclusive o binário)
fclean: clean
	rm -f $(NAME)

# Recompila tudo do zero
re: fclean all

# Garante que make não delete arquivos intermediários
.PHONY: all clean fclean re
-include $(DEP)
