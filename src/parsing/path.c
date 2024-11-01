/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 01:44:17 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 22:02:16 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_command_in_path(char *command)
{
	char	*path;
	char	*path_copy;
	char	*original_ptr;
	char	*dir;

	if (!command)
		return (ERROR);
	path = getenv("PATH");
	if (!path)
		return (ERROR);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (ERROR);
	original_ptr = path_copy;
	dir = get_next_path(&path_copy);
	while (dir)
	{
		if (!check_single_path(dir, command))
			return (free(original_ptr), SUCCESS);
		dir = get_next_path(&path_copy);
	}
	free(original_ptr);
	return (ERROR);
}

char	*get_next_path(char **path)
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

int	check_single_path(char *dir, char *command)
{
	char	*full_path;
	char	*tmp;
	int		status;

	if (!dir || !command)
		return (ERROR);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (ERROR);
	full_path = ft_strjoin(tmp, command);
	free(tmp);
	if (!full_path)
		return (ERROR);
	status = access(full_path, X_OK);
	free(full_path);
	return (status);
}
