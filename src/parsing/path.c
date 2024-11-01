/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 01:44:17 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 02:42:57 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_command_in_path(char *command)
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	*path_ptr;

	path_env = getenv("PATH");
	if (!path_env)
		return (ERROR);
	path = ft_strdup(path_env);
	if (!path)
		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
	path_ptr = path;
	dir = get_next_path(&path_ptr);
	while (dir)
	{
		if (check_single_path(dir, command))
			return (free(path), free(dir), ERROR);
		dir = get_next_path(&path_ptr);
	}
	free(path);
	return (SUCCESS);
}

bool	check_single_path(char *dir, char *command)
{
	char	*full_path;
	char	*tmp;

	full_path = ft_strjoin(dir, "/");
	if (!full_path)
		return (free(dir), cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
	tmp = ft_strjoin(full_path, command);
	free(full_path);
	free(dir);
	if (!tmp)
		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
	full_path = tmp;
	if (access(full_path, F_OK | X_OK) == 0)
		return (free(full_path), SUCCESS);
	free(full_path);
	return (ERROR);
}

char	*get_next_path(char **path_ptr)
{
	char	*start;
	char	*end;
	char	*dir;
	int		len;

	if (!*path_ptr || !**path_ptr)
		return (NULL);
	start = *path_ptr;
	end = start;
	while (*end && *end != ':')
		end++;
	len = end - start;
	dir = malloc(len + 1);
	if (!dir)
		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2), NULL);
	ft_strlcpy(dir, start, len + 1);
	if (*end == ':')
		*path_ptr = end + 1;
	else
		*path_ptr = end;
	return (dir);
}
