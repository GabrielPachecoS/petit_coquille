# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:08:24 by gapachec          #+#    #+#              #
#    Updated: 2025/06/02 21:25:43 by jucoelho         ###   ########.fr        #
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
		  $(SRC_DIR)/exec/exec.c \
		  $(SRC_DIR)/exec/path.c \
		  $(SRC_DIR)/lexer/lexer.c \
		  $(SRC_DIR)/lexer/lexer_1_utils.c \
		  $(SRC_DIR)/lexer/lexer_2_utils.c \
		  $(SRC_DIR)/lexer/lexer_handle.c \
		  $(SRC_DIR)/parser/parser.c \
		  $(SRC_DIR)/parser/parser_utils.c


CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INC		= -I$(INC_DIR) -I$(LIBFT_DIR)

# Geração automática dos .o a partir dos .c
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Instrução para incluir dependências (geradas com -MMD)
DEP		= $(OBJ:.o=.d)

all: $(LIBFT_DIR)/libft.a $(OBJ_DIR) $(OBJ_DIR)/lexer $(OBJ_DIR)/parser $(NAME)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)
	
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

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/exec:
	mkdir -p $(OBJ_DIR)/exec

$(OBJ_DIR)/lexer:
	mkdir -p $(OBJ_DIR)/lexer

$(OBJ_DIR)/parser:
	mkdir -p $(OBJ_DIR)/parser

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
# Limpa tudo (inclusive o binário)
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
re: fclean all

.PHONY: all clean fclean re
-include $(DEP)
