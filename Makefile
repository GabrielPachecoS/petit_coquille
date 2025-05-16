# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:08:24 by gapachec          #+#    #+#              #
#    Updated: 2025/05/16 09:43:09 by gapachec         ###   ########.fr        #
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

# Lista de arquivos fonte (você vai adicionando os outros aqui)
SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/start_minishell.c \
		  $(SRC_DIR)/signals.c \
		  $(SRC_DIR)/cleanup.c

# Geração automática dos .o a partir dos .c
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Instrução para incluir dependências (geradas com -MMD)
DEP		= $(OBJ:.o=.d)

# Regra padrão
all: $(NAME)

# Como compilar o binário
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Como compilar os .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -MMD -c $< -o $@

# Cria o diretório obj se não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

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
