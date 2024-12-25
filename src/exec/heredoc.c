/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:19:57 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/25 20:21:24 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	destroy_heredoc_process(int exit_status, char **to_be_free)
{
	t_data	*data;

	data = get_data();
	if (to_be_free)
		ft_free_multi_array(to_be_free);
	if (data)
	{
		if (data->envp)
			destroy_envp_list(&data->envp);
		free_data(&data);
		if (data->line)
			free(data->line);
	}
	rl_clear_history();
	exit(exit_status);
}

void	heredoc_child_process(char *limiter)
{
	t_data	*data;
	char	*line;

	data = get_data();
	close(data->pip[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document");
			printf("delimited by end-of-file) (wanted `%s')\n", limiter);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, data->pip[1]);
		ft_putstr_fd("\n", data->pip[1]);
		free(line);
	}
	close(data->pip[1]);
}

int	heredoc_parent_process(int fd, t_data *data)
{
	char	buffer[4096];
	int		bytes_read;

	close(data->pip[1]);
	bytes_read = read(data->pip[0], buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(fd, buffer, bytes_read);
		bytes_read = read(data->pip[0], buffer, sizeof(buffer));
	}
	close(data->pip[0]);
	return (SUCCESS);
}

int	heredoc_cpy(int fd, char *limiter)
{
	t_data	*data;

	data = get_data();
	if (pipe(data->pip) == -1)
		return (ERROR);
	data->current_pid = fork();
	signal(SIGINT, &signals_heredoc);
	if (data->current_pid == -1)
		return (close(data->pip[0]), close(data->pip[1]), ERROR);
	if (data->current_pid == 0)
	{
		heredoc_child_process(limiter);
		destroy_child_process(SUCCESS, NULL);
		return (SUCCESS);
	}
	else
		return (heredoc_parent_process(fd, data));
}

int	heredoc(t_cmd *cmd, char *limiter)
{
	t_data	*data;
	int		status;

	data = get_data();
	if (cmd->infile >= 0)
		close(cmd->infile);
	cmd->infile = open("/tmp/.minishell.heredoc", O_CREAT | O_RDWR | O_TRUNC,
			0644);
	if (cmd->infile == -1)
		return (ERROR);
	if (heredoc_cpy(cmd->infile, limiter) == ERROR)
		return (close(cmd->infile), unlink("/tmp/.minishell.heredoc"), ERROR);
	close(cmd->infile);
	cmd->infile = open("/tmp/.minishell.heredoc", O_RDONLY);
	if (cmd->infile == -1)
		return (ERROR);
	waitpid(0, &status, 0);
	if (WIFEXITED(status))
	{
		data->exit_status = WEXITSTATUS(status);
		if (data->exit_status == 130)
			return (close(cmd->infile), setup_signals(), cleanup(130, NULL,
					NO_EXIT, 0), ERROR);
	}
	return (setup_signals(), SUCCESS);
}
