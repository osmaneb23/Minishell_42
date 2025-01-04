/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:34:24 by febouana          #+#    #+#             */
/*   Updated: 2025/01/04 16:48:29 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_all(t_data *data)
{
	t_cmd	*cmd;
	int		status;
	int		pid;

	cmd = data->cmd;
	while (cmd)
	{
		pid = waitpid(0, &status, 0);
		if (pid == -1)
			return (cleanup(ERROR, ERR_WAIT, ERROR, 2));
		if (pid == data->current_pid)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			if (data->exit_status == EXIT_MALLOC)
				cleanup(EXIT_MALLOC, ERR_MALLOC, EXIT_MALLOC, 2);
		}
		cmd = cmd->next;
	}
	data->current_pid = 0;
	return (SUCCESS);
}

char	*get_path_next(char **path)
{
	char	*dir;
	char	*next;

	if (!path || !*path)
		return (NULL);
	dir = *path;
	next = ft_strchr(*path, ':');
	if (next)
	{
		*next = '\0';
		*path = next + 1;
	}
	else
		*path = NULL;
	return (dir);
}

char	*check_solo_path(char *dir, char *command)
{
	char	*full_path;
	char	*tmp;

	if (!dir || !command)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, command);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	else
	{
		free(full_path);
		return (NULL);
	}
}

char	*return_command_in_path(char *command)
{
	char	*path;
	char	*path_copy;
	char	*original_ptr;
	char	*dir;
	char	*full_path;

	if (!command)
		return (NULL);
	path = search_env_var("PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (NULL);
	original_ptr = path_copy;
	dir = get_path_next(&path_copy);
	while (dir)
	{
		full_path = check_solo_path(dir, command);
		if (full_path)
			return (free(original_ptr), full_path);
		dir = get_path_next(&path_copy);
	}
	free(original_ptr);
	return (NULL);
}

void	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}
