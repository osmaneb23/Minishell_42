DEFAULT = \033[0m
WHITE = \033[0;37m
BWHITE = \033[1;37m
RED = \033[0;31m
BRED = \033[1;31m

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

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT = Libft/libft.a

SRC_DIR = src
OBJ_DIR = obj
INCLUDES = includes

SRCS = main.c \
       parsing/checks.c \
       parsing/path.c \
       parsing/token_type.c \
       parsing/tokenization.c \
       utils/cleaning.c \
       utils/data.c \
       utils/signals.c \
       utils/toolbox.c \
       utils/utils_checks.c \
       utils/utils_dollar.c \
       utils/utils_dollar2.c \
       utils/utils_token.c \
       builtins/ft_cd.c \
       builtins/ft_env.c \
       builtins/ft_export.c \
       builtins/ft_pwd.c \
       builtins/ft_unset.c \
       builtins/ft_exit.c \
       builtins/ft_echo.c \
       builtins/utils/builtins_utils.c \
       builtins/utils/envp_utils.c \
       builtins/utils/ft_export_utils.c \
       builtins/utils/ft_export_utils2.c \
       exec/commands.c \
       exec/commands_utils.c \
       exec/exec.c \
       exec/exec_utils.c \
       exec/launch_builtin.c \
       exec/heredoc.c \
       exec/redirection_gestion.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

SRC_SUBDIRS = parsing utils builtins exec
OBJ_SUBDIRS = $(addprefix $(OBJ_DIR)/,$(SRC_SUBDIRS))

RM = rm -rf
VAL_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=supp.supp

all: $(NAME)

env: $(NAME)
	env -i valgrind $(VAL_FLAGS) ./$(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(WHITE)Linking objects...$(DEFAULT)"
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)
	@printf "\n${WHITE}$$BANNER${DEFAULT}\n\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	@echo "$(WHITE)Compiling $<...$(DEFAULT)"
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C Libft --no-print-directory

clean:
	@$(RM) $(OBJ_DIR)
	@make -C Libft clean --no-print-directory
	@echo "$(BRED)Objects removed!$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@make -C Libft fclean --no-print-directory
	@echo "$(BRED)Executable removed!$(DEFAULT)"

re: fclean all
	@echo "$(BGREEN)Recompiled successfully!$(DEFAULT)"

valgrind: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)
	
.PHONY: all clean fclean re valgrind
