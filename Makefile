# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 18:40:22 by obouayed          #+#    #+#              #
#    Updated: 2024/10/21 19:00:19 by obouayed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = minishell

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT = Libft/libft.a

# Source files and object files
SRC = main.c
SRC_DIR = src
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Includes file
HEADER = includes/minishell.h

# Commands
RM = rm -rf
VAL_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

# Compilation
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(HEADER)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
		@echo "Compilation done!"
		
$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c | $(OBJ_DIR)
		$(CC) -c $< -o $@

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

$(LIBFT):
		make -C Libft

# Cleaning
clean:
	$(RM) $(OBJ_DIR)
	make -C Libft clean
	@echo "Objects removed!"

fclean: clean
	$(RM) $(NAME)
	make -C Libft fclean
	@echo "Executable removed!"

# Re-compile everything
re: fclean all
	make -C Libft re

# Debugging
valgrind: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)

# To prevent commands from being treated as files
.PHONY: all clean fclean re valgrind
