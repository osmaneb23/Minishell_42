# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 18:40:22 by obouayed          #+#    #+#              #
#    Updated: 2024/10/29 18:36:55 by obouayed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEFAULT = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

# Bold Colors
BBLACK = \033[1;30m
BRED = \033[1;31m
BGREEN = \033[1;32m
BYELLOW = \033[1;33m
BBLUE = \033[1;34m
BPURPLE = \033[1;35m
BCYAN = \033[1;36m
BWHITE = \033[1;37m

define BANNER

 ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗
 ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     
 ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     
 ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     
 ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
 ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
                                    by obouayed and febouana        
endef
export BANNER

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
	   utils/utils_checks.c \
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
	@echo "$(CYAN)Linking objects...$(DEFAULT)"
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)
	@printf "\n${BLUE}$$BANNER${DEFAULT}\n\n"

# Create object directories and compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(DEFAULT)"
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

# Compile libft
$(LIBFT):
	@make -C Libft

# Cleaning rules
clean:
	@$(RM) $(OBJ_DIR)
	@make -C Libft clean
	@echo "$(BRED)Objects removed!$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@make -C Libft fclean
	@echo "$(BRED)Executable removed!$(DEFAULT)"

re: fclean all
	@echo "$(BGREEN)Recompiled successfully!$(DEFAULT)"

# Debugging
valgrind: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)
	
# To prevent commands from being interpreted as files
.PHONY: all clean fclean re valgrind