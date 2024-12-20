/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:19:57 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/20 19:20:13 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	escape_heredoc(char *limiter)
{
	printf("minishell: warning: here-document delimited by end-of-file (wanted '%s')\n",
		limiter);
}

//! cas prevu si ctrl-D ...mais ctrl-C ?
int	heredoc_cpy(int fd, char *limiter)
{
	char	*line;

	line = "";
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			escape_heredoc(limiter);
			break;
		}
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	close(fd);
	fd = open("/tmp/.minishell.heredoc.", O_RDONLY);
	if (fd == -1)
		return (ERROR);
	return (SUCCESS);
}

int	heredoc(t_cmd *cmd, char *limiter)
{
	if (cmd->infile >= 0)
		close(cmd->infile);
	cmd->infile = open("/tmp/.minishell.heredoc.", O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (cmd->infile == -1)
		return (ERROR);
	if (heredoc_cpy(cmd->infile, limiter) != SUCCESS)
	{
		close(cmd->infile);
		unlink("/tmp/.minishell.heredoc.");
		cleanup(0, NULL, NO_EXIT, 1);
		return (FAILURE);
	}
	unlink("/tmp/.minishell.heredoc.");
	printf("\n");
	return (SUCCESS);
}

// exit status heredoc ctrl-D ==> 0
// exit status heredoc ctrl-C ==> 130
//! si exit du coup != ctrl-D (ligne 60)