/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:03:56 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/22 18:14:59 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/get_next_line.h" // get_next_line
# include "../Libft/libft.h"         // libft
# include <fcntl.h>                  // open, close
# include <linux/limits.h>           // INT_MAX, INT_MIN, PATH_MAX etc
# include <stdio.h>                  // printf
# include <readline/history.h>       // add_history
# include <readline/readline.h>      // readline
# include <signal.h>                 // signal
# include <stdbool.h>                // bool
# include <stdlib.h>                 // malloc, free, exit
# include <sys/stat.h>               // stat
# include <sys/types.h>              // pid_t
# include <sys/wait.h>               // waitpid
# include <unistd.h>                 // execve, fork, pipe

# define SUCCESS 0
# define ERROR 1
# define FAILURE -1
# define TRUE 1
# define FALSE 0
# define NO_EXIT -42

# define INPUT 1   // <
# define HEREDOC 2 // <<
# define TRUNC 3   // >
# define APPEND 4  // >>
# define PIPE 5    // |
# define CMD 6     // command
# define ARG 7     // argument

/*
Structure to store the commands:
- infile: file descriptor of the input file
- outfile: file descriptor of the output file
- cmd_param: array of strings containing the command and its arguments
- next: pointer to the next command
- prev: pointer to the previous command
*/
typedef struct s_cmd
{
	char			**cmd_param;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;

	pid_t 			f_pid;
}					t_cmd;


/*
Structure to store the environment variables:
- line: the line of the environment variable
- next: pointer to the next environment variable
- prev: pointer to the previous environment variable
*/
typedef struct s_env
{
	char			*line;
	struct s_env	*next;
	struct s_env	*prev;

}					t_env;

/*
Structure to store the tokens:
- value: value of the current token
- type: type of the  current token (between 1 and 7)
[1: INPUT, 2: HEREDOC, 3: TRUNC, 4: APPEND, 5: PIPE, 6: CMD, 7: ARG]
- next: pointer to the next token
- prev: pointer to the previous token
*/
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;

}					t_token;

/*
Structure to store the data of minishell:
- token: first token of the list
- envp: first environment variable of the list
- cmd: first command of the list
- line: current line entered by the user
- exit_status: exit status of the last line
*/
typedef struct s_data
{
	int 			pip[2];
	
	t_token			*token;
	t_env			*envp;
	t_cmd			*cmd;
	char			*line;
	int				exit_status;
	pid_t			current_pid;
}					t_data;

// Main

bool				main_routine(t_data *data, char **envp);

/* ************************************************************************** */
/*                                                                            */
/*                                    EXEC                                    */
/*                                                                            */
/* ************************************************************************** */

// exec.c
int 				exec();

// exec_utils.c
int					wait_all(t_data *data);
int 				t_cmd_len(t_cmd *cmd);


// Commands
//!
int count_nbr_cmd(t_token *token);
int	init_cmd_nodes(t_data *data);
int init_cmd(t_data *data);
//!
// void				init_cmd(t_data *data);
// char	**init_cmd_param(t_cmd *cmd, t_token *token);
bool				add_cmd_to_list(t_cmd *cmd, t_cmd *data_cmd);



/* ************************************************************************** */
/*                                                                            */
/*                                    BUILTINS                                */
/*                                                                            */
/* ************************************************************************** */

// ft_pwd.c //OKOK
int 				ft_pwd(void);

// ft_env.c //OKOK
int 				ft_env(void);

// ft_unset.c //OKOK
int 				search_and_del(char *var);
int 				ft_unset(char **cmd_param);

// ft_cd.c //OKOK
char *search_env_var(char *var);
int 				change_cd(char *direction);
int 				ft_cd(char **cmd_param);

// ft_export.c //OKOK
int 				print_export_line(char *line);
int 				export_just_new_var(t_env *envp, char *var);
int 				export_new_var_and_val(t_env *envp, char *var_and_val);
int 				export_just_display(t_data *data);
int 				ft_export(char **cmd_param);

// ft_exit.c //OKOK
int					ft_exit(char **args);

//! ft_echo.c

/* ************************************************************************** */
/*                                                                            */
/*                              BUILTINS UTILS                                */
/*                                                                            */
/* ************************************************************************** */

// init_envp.c //OKOK
t_env				*find_last_node(t_env *node);
void				del_node_t_env(t_env **envp);
int					append_node_envp(t_env **envp, char *line);
int 				make_env_if_le_correcteur_clc(t_data* data);
void				make_env(t_data *data, char **env);

// utils_export.c //OKOK
int 				verif_var_char(char *var);
int 				remplace_if_already_exist(char *var, char* val);
int 				envp_tab_bubble_sort(char **envp, int count);
int 				sort_envp_and_print(char **envp, int count);
char 				**copy_envp_to_tab(t_data *data, t_env *envp);

// builtins_utils.c //OKOK
void				ft_free_tabtab(char **tabtab);
int 				tabtablen(char **s);
char				*join_var_and_val(char const *s1, char const *s2);
int					 count_envp_nodes(t_env *envp);

/* ************************************************************************** */
/*                                                                            */
/*                                  PARSING                                   */
/*                                                                            */
/* ************************************************************************** */

// Checks

bool				check_openquote(char *line);
int					check_misplacements(t_data *data);
int					check_valid_commands(t_data *data);

// Path

int					check_command_in_path(char *command);
char				*get_next_path(char **path);
int					check_single_path(char *dir, char *command);

// Token_type

void				assign_type_to_tokens(void);
int					determine_basic_type(char *value);

// Tokenization

bool				tokenization(char *line);
char				*tokenizer(char *line, unsigned int *i, bool *squote_open,
						bool *dquote_open);
char				*handle_quote(char *line, unsigned int *i,
						bool *squote_open, bool *dquote_open);
bool				create_token(char *value);
bool				add_token_to_list(t_token *token, t_token *data);

/* ************************************************************************** */
/*                                                                            */
/*                                    UTILS                                   */
/*                                                                            */
/* ************************************************************************** */

// Cleaning

int					cleanup(int exit_status, char *message, int exit_call,
						int fd);
void				free_data(t_data **data);
void				free_tokens(t_data **data);
void				free_commands(t_data **data);

// Data

void				*get_data(void);
void				initialize_data(t_data **data);

// Signals

void				setup_signals(void);
void				sigint_handler(int sig);
void				sigquit_handler(int sig);

// Toolbox

bool				contains_char(char *str, char c);

// Utils_checks

int					check_misplacements_pipe(t_token *token);
int					check_misplacements_redirection(t_token *token);
bool				is_builtin(char *cmd);
int					check_access(t_token *token);

// Utils_cmd

t_cmd				*last_command(t_cmd *command);

// Utils_token

t_token				*last_token(t_token *token);
void				remove_quotes(t_data *data);
char				*return_new_value(char *value, bool squote_open,
						bool dquote_open);
void				printf_tokens(t_data *data);

#endif