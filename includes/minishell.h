/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:03:56 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/24 22:10:09 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../Libft/get_next_line.h" // get_next_line
# include "../Libft/libft.h"         // libft
# include <fcntl.h>                  // open, close
# include <linux/limits.h>
# include <stdio.h>    
# include <readline/history.h>       // add_history
# include <readline/readline.h>      // readline
# include <signal.h>                 // signal
# include <stdbool.h>                // bool              // printf
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

typedef struct t_data
{
	char        *username;
    char        *cwd;
    // t_list      *env;
}					t_data;

struct				s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;

}					t_token;

void *get_data();
int ft_pwd();
int ft_cd(char *direction);

#endif


