# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:08:24 by gapachec          #+#    #+#              #
#    Updated: 2025/05/16 09:00:35 by gapachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = *.c #arrumar
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

$(NAME): $(OBJ)
        $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
        @mkdir -p $(OBJ_DIR)
        $(CC) $(CFLAGS) -c $< -o $@

clean:
        rm -rf $(OBJ_DIR)

fclean: clean
        rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all fclean clean re
