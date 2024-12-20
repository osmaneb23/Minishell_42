/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:19:57 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/20 22:39:57 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_sigint_handler(int sig)
{
	t_data	*data;

	data = get_data();
	(void)sig;
	if (data->current_pid == 0)
    {
        ft_putstr_fd("\n", 2);
        data->exit_status = 130;
		exit(130);
    }
}

void	escape_heredoc(char *limiter)
{
	printf("minishell: warning: here-document delimited by end-of-file (wanted '%s')\n",
		limiter);
}

//! cas prevu si ctrl-D ...mais ctrl-C ?
int	heredoc_cpy(int fd, char *limiter)
{
	char	*line;
	int		pip[2];
	t_data	*data;
		char buffer[1024];
		int bytes_read;

	data = get_data();
	if (pipe(pip) == -1)
		return (ERROR);
	data->current_pid = fork();
    setup_signals();
	if (data->current_pid == -1)
	{
		close(pip[0]);
		close(pip[1]);
		return (ERROR);
	}
	if (data->current_pid == 0) // Child
	{
		close(pip[0]); // Close read end
		while (1)
		{
			line = readline("> ");
			if (!line) // Handle EOF (Ctrl+D)
			{
				escape_heredoc(limiter);
				close(pip[1]);
				exit(EXIT_SUCCESS);
			}
			if (ft_strcmp(line, limiter) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, pip[1]); // Write to pipe instead of STDOUT
			ft_putstr_fd("\n", pip[1]);
			free(line);
		}
		close(pip[1]);
		exit(EXIT_SUCCESS);
	}
	else // Parent
	{
		close(pip[1]); // Close write end
		while ((bytes_read = read(pip[0], buffer, sizeof(buffer))) > 0)
		{
			write(fd, buffer, bytes_read); // Write to parent's fd
		}
		close(pip[0]);
		return (SUCCESS);
	}
}

int	heredoc(t_cmd *cmd, char *limiter)
{
	int	status;

	if (cmd->infile >= 0)
		close(cmd->infile);
	// cmd->infile = open("/tmp/.minishell.heredoc.",
			// O_CREAT | O_WRONLY | O_TRUNC,
	// 		0644);
	// if (cmd->infile == -1)
	// 	return (ERROR);
	// cmd->infile = open("/tmp/.minishell.heredoc.",
			// O_CREAT | O_RDWR | O_TRUNC);
	heredoc_cpy(cmd->infile, limiter);
	waitpid(0, &status, 0);
	// if ctrl D et error
	// {
	// 	// close(cmd->infile);
	// 	unlink("/tmp/.minishell.heredoc.");
	// 	cleanup(0, NULL, NO_EXIT, 1);
	// 	return (FAILURE);
	// }
	// signal(SIGINT, SIG_IGN);
	return (SUCCESS);
}

// exit status heredoc ctrl-D ==> 0
// exit status heredoc ctrl-C ==> 130
//! si exit du coup != ctrl-D (ligne 60)