/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:19:57 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/17 23:16:52 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	escape_heredoc(char *limiter)
{
	print_error("minishell: warning: here-document delimited\
		by end-of-file (wanted '");
	print_error(limiter);
	print_error("')\n");
}

//! cas prevu si ctrl-D ...mais ctrl-C ?
bool	heredoc_cpy(int fd, char *limiter)
{
	char	*line;

	line = "";
	while (1)
	{
		line = readline("> ");
		if (!line)
			escape_heredoc(limiter);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(line);
	close(fd);
	fd = open(".minishell.heredoc.tmp", O_RDONLY);
	if (fd == -1)
		return (false);
	return (true);
}

int	heredoc(t_cmd *cmd, char *limiter)
{
	t_data	*data;

	data = get_data();
	if (cmd->infile >= 0)
		close(cmd->infile);
	cmd->infile = open(".minishell.heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (cmd->infile == -1)
		return (ERROR);
	if (!heredoc_cpy(cmd->infile, limiter))
	{
		unlink(".minishell.heredoc.tmp");
		close_all_redi(data);
		return (FAILURE);
	}
	unlink(".minishell.heredoc.tmp");
	printf("\n");
	return (SUCCESS);
}
