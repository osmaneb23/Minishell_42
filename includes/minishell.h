/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:03:56 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/22 21:07:39 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/get_next_line.h" // get_next_line
# include "../Libft/libft.h"         // libft
# include <fcntl.h>                  // open, close
# include <limits.h>                 // INT_MAX, INT_MIN etc
# include <readline/history.h>       // add_history
# include <readline/readline.h>      // readline
# include <signal.h>                 // signal
# include <stdbool.h>                // bool
# include <stdio.h>                  // printf
# include <stdlib.h>                 // malloc, free, exit
# include <sys/stat.h>               // stat
# include <sys/types.h>              // pid_t
# include <sys/wait.h>               // waitpid
# include <unistd.h>                 // execve, fork, pipe

# define SUCCESS 0
# define ERROR 1
# define FAIL -1
# define TRUE 1
# define FALSE 0

# define INPUT 1   // <
# define HEREDOC 2 // <<
# define TRUNC 3   // >
# define APPEND 4  // >>
# define PIPE 5    // |
# define CMD 6     // command
# define ARG 7     // argument

typedef struct				s_token
{
	char			*value;
	int				type;
	unsigned int 	index;
	struct s_token	*next;
	struct s_token	*prev;

}					t_token;

#endif