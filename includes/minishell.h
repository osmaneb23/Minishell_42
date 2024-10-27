/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:03:56 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/27 03:45:56 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/get_next_line.h" // get_next_line
# include "../Libft/libft.h"         // libft
# include <fcntl.h>                  // open, close
# include <limits.h>                 // INT_MAX, INT_MIN etc
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
- line: current line entered by the user
- username: username of the user
- exit_status: exit status of the last line
*/
typedef struct s_data
{
	t_token			*token;
	char			*line;
	char			*username;
	char			**env;
	int				exit_status;
}					t_data;

// Initialization functions

void				initialize_data(t_data **data, char **env);
void				assign_type_to_tokens(void);
int					determine_basic_type(char *value);

// Parsing functions

int					check_misplacements(t_data *data);
int					check_misplacements_pipe(t_token *token);
int					check_misplacements_redirection(t_token *token);
bool				openquote(char *line);
int					check_valid_commands(t_data *data);

// Tokenization functions

bool				tokenization(char *line);
char				*tokenizer(char *line, unsigned int *i, bool *squote_open,
						bool *dquote_open);
char				*handle_quote(char *line, unsigned int *i,
						bool *squote_open, bool *dquote_open);
bool				create_token(char *value);
bool				add_token_to_list(t_token *new, t_token *token);

// Utils functions

void				*get_data(void);
void				printf_tokens(t_data *data);
t_token				*last_token(t_token *token);

// Cleaning functions

int					cleanup(int exit_status, char *message, int exit_call,
						int fd);
void				free_data(t_data **data);
void				free_tokens(t_data **data);

#endif