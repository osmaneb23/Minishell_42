/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 01:44:17 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 01:50:50 by obouayed         ###   ########.fr       */
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
		return (FALSE);
	path = ft_strdup(path_env);
	if (!path)
		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
	path_ptr = path;
	dir = get_next_path(&path_ptr);
	while (dir)
	{
		if (check_single_path(dir, command, path))
			return (TRUE);
		dir = get_next_path(&path_ptr);
	}
	free(path);
	return (FALSE);
}

bool	check_single_path(char *dir, char *command, char *path)
{
	char	*full_path;
	char	*tmp;

	full_path = ft_strjoin(dir, "/");
	if (!full_path)
		return (free(dir), free(path), cleanup(ERROR, "Error: malloc failed\n",
				ERROR, 2), FALSE);
	tmp = ft_strjoin(full_path, command);
	free(full_path);
	free(dir);
	if (!tmp)
		return (free(path), cleanup(ERROR, "Error: malloc failed\n", ERROR, 2),
			FALSE);
	full_path = tmp;
	if (access(full_path, F_OK | X_OK) == 0)
		return (free(full_path), true);
	free(full_path);
	return (FALSE);
}
