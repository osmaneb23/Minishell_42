# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 18:40:22 by obouayed          #+#    #+#              #
#    Updated: 2024/10/27 01:23:11 by obouayed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = minishell

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT = Libft/libft.a

# Directory structure
SRC_DIR = src
OBJ_DIR = obj
INCLUDES = includes

# Source files with their paths
SRCS = main.c \
       parsing/checks.c \
       parsing/token_type.c \
       parsing/tokenization.c \
       utils/cleaning.c \
       utils/data.c \
       utils/utils_token.c

# Generate object file paths
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Create lists of subdirectories
SRC_SUBDIRS = parsing utils builtins exec
OBJ_SUBDIRS = $(addprefix $(OBJ_DIR)/,$(SRC_SUBDIRS))

# Commands
RM = rm -rf
VAL_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

# Compilation rules
all: $(NAME)

# Create necessary directories and compile
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)
	@echo "Compilation done!"

# Create object directories and compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

# Compile libft
$(LIBFT):
	make -C Libft

# Cleaning rules
clean:
	$(RM) $(OBJ_DIR)
	make -C Libft clean
	@echo "Objects removed!"

fclean: clean
	$(RM) $(NAME)
	make -C Libft fclean
	@echo "Executable removed!"

re: fclean all

# Debugging
valgrind: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)
	
# To prevent commands from being interpreted as files
.PHONY: all clean fclean re valgrind