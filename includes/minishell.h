/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:03:56 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/12 17:20:22 by apoet            ###   ########.fr       */
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
# include <limits.h>

# define SUCCESS 0
# define ERROR 1
# define FAILURE -1
# define TRUE 1
# define FALSE 0
# define NO_EXIT -42
# define NO_CHANGE -42

# define EXIT_MALLOC -42

# define INPUT 1   // <
# define HEREDOC 2 // <<
# define TRUNC 3   // >
# define APPEND 4  // >>
# define PIPE 5    // |
# define CMD 6     // command
# define ARG 7     // argument

# define ERR_MALLOC "Error: malloc failed\n"
# define ERR_PIPE "Error: pipe failed\n"
# define ERR_FORK "Error: fork failed\n"
# define ERR_WAIT "Error: wait failed\n"



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
	pid_t			f_pid;

	bool			skip_cmd;
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
	int				pip[2];

	t_token			*token;
	t_env			*envp;
	t_cmd			*cmd;
	char			*line;
	int				exit_status;
	pid_t			current_pid;
}					t_data;

/* ************************************************************************** */
/*                                    MAIN                                    */
/* ************************************************************************** */

void				init_env(t_data *data, char **env);
void				replace_var_val(t_data *data);
bool				main_routine(t_data *data, char **envp);
bool				print_error(char *str);

/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

// ft_pwd.c
bool				ft_pwd(void);

// ft_env.c
int					ft_env(void);

// ft_unset.c
int					search_and_del(char *var);
int					ft_unset(char **cmd_param);

// ft_cd.c
char				*search_env_var(char *var);
int					change_cd(char *direction);
int					ft_cd(char **cmd_param);

// ft_export.c
void					print_export_line(char *line);
int					export_just_new_var(t_env *envp, char *var);
int					export_new_var_and_val(t_env *envp, char *var_and_val,
						int i);
void					export_just_display(t_data *data);
int					ft_export(char **cmd_param);

// ft_exit.c
int					ft_exit(char **cmd_param);

// ft_echo.c
int					ft_echo(char **cmd_param);

/* ************************************************************************** */
/*                             (BUILTINS) UTILS                               */
/* ************************************************************************** */

// builtins_utils.c
void				ft_free_multi_array(char **tabtab);
int					ft_multi_array_len(char **s);
char				*join_var_and_val(char const *s1, char const *s2);
int					count_envp_nodes(t_env *envp);

// envp_utils.c
void				destroy_envp_list(t_env **envp);
t_env				*find_last_node(t_env *node);
void				del_node_envp(t_env **envp);
int					append_node_envp(t_env **envp, char *line);
int					init_env_if_le_correcteur_clc(t_data *data);

// ft_export_utils.c
int					search_egal_symbol(char *cmd_param);
char				*return_var(char *var_and_val, int limit);
char				*return_val(char *var_and_val, int start);

// ft_export_utils2.c
bool					verif_var_char(char *var);
int					remplace_if_already_exist(char *var, char *val);
void					envp_tab_bubble_sort(char **envp, int count);
void					sort_envp_and_print(char **envp, int count);
char				**copy_envp_to_tab(t_data *data, t_env *envp);

/* ************************************************************************** */
/*                                    EXEC                                    */
/* ************************************************************************** */

// exec.c
void					redirect_input_output(t_cmd *cmd, int *pip);
void					parent_process(int *pip, t_cmd *next_cmd);
void					child_process(t_cmd *cmd, int *pip, char **env);
int					exec_cmd(t_data *data, t_cmd *cmd, int *pip);
int					exec(t_data *data);

// exec_utils.c
int					wait_all(t_data *data);
char				*get_path_next(char **path);
char				*check_solo_path(char *dir, char *command);
char				*return_command_in_path(char *command);

// heredoc.c
void				escape_heredoc(char *limiter);
bool				heredoc_cpy(int fd, char *limiter);
int					heredoc(t_cmd *cmd, char *limiter);

// launch_builtin.c
void				exec_builtin(char **cmd);
void				launch_builtin(t_cmd *cmd);

// commands.c
int					count_cmd_param(t_token *og_token);
char				**init_cmd_param(t_token *og_token);
int					fill_cmd_nodes(t_data *data);
int					init_cmd_nodes(t_data *data);
int					init_cmd(t_data *data);

// commands_utils.c
int					cmd_list_len(t_cmd *cmd);
int					add_cmd_to_list(t_cmd *cmd, t_cmd *data_cmd);
int					count_nb_sequences(t_token *token);
t_cmd				*return_last_cmd_node(t_cmd *command);
void				free_all_cmd_nodes(t_cmd **cmd_list);

// gestion_redirections.c
int					close_all_redi(t_data *data);
void				close_all_redi_of_each_nodes(t_data *data);
int					fill_cmd_nodes_redirections(t_cmd *cmd, t_token *token);
int					init_file(t_cmd *cmd, char *filename, int type);

/* ************************************************************************** */
/*                                  PARSING                                   */
/* ************************************************************************** */

// checks.c
bool				check_openquote(char *line);
int					check_misplacements(t_data *data);
int					check_valid_commands(t_data *data);

// path.c
int					check_command_in_path(char *command);
char				*get_next_path(char **path);
int					check_single_path(char *dir, char *command);

// token_type.c
void				assign_type_to_tokens(void);
int					determine_basic_type(char *value);

// tokenization.c
bool				tokenization(char *line);
char				*tokenizer(char *line, unsigned int *i, bool *squote_open,
						bool *dquote_open);
char				*handle_quote(char *line, unsigned int *i,
						bool *squote_open, bool *dquote_open);
bool				create_token(char *value);
bool				add_token_to_list(t_token *token, t_token *data);

/* ************************************************************************** */
/*                                    UTILS                                   */
/* ************************************************************************** */

// cleaning.c
int					cleanup(int exit_status, char *message, int exit_call,
						int fd);
void				free_data(t_data **data);
void				free_tokens(t_data **data);
void				free_commands(t_data **data);

// data.c
void				*get_data(void);
void				initialize_data(t_data **data);

// signals.c
void				setup_signals(void);
void				sigint_handler(int sig);
void				sigquit_handler(int sig);

// toolbox.c
bool				contains_char(char *str, char c);

// utils_checks.c
int					check_misplacements_pipe(t_token *token);
int					check_misplacements_redirection(t_token *token);
bool				is_builtin(char *cmd);
int					check_access(t_token *token);

// utils_cmd.c
t_cmd				*return_last_cmd_node(t_cmd *command);

// utils_dollar.c
void				main_handle_var(char *tmp, char *new_value, t_data *data);
int					handle_exit_status(t_data *data, char *new_value, int j,
						int *i);
int					handle_var_names(int *i, char *tmp, char *new_value, int j);
int					str_append(char *dest, const char *src, int pos);
size_t				ft_numlen(int n);

size_t				estimate_new_length(const char *value, t_data *data);
size_t				handle_dollar_sign(const char *value, int *i, t_data *data);
size_t				get_exit_status_length(int status);
size_t				skip_variable_name(const char *str);
size_t				get_env_var_length(const char *start, int len);

// utils_token.c
t_token				*last_token(t_token *token);
void				remove_quotes(t_data *data);
char				*return_new_value(char *value, bool squote_open,
						bool dquote_open);
void				printf_tokens(t_data *data);

#endif
