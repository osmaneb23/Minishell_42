// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   path.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/29 19:53:54 by obouayed          #+#    #+#             */
// /*   Updated: 2024/10/29 20:14:56 by obouayed         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// int	check_command_path_access(char *cmd)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '/' || cmd[i] == '.')
// 		{
// 			if (access(cmd, F_OK | X_OK) != 0)
// 				return (FALSE);
// 		}
// 		i++;
// 	}
// 	return (TRUE);
// }

// int	init_path_check(char **path_env, char **path)
// {
// 	*path_env = getenv("PATH");
// 	if (!*path_env)
// 		return (ERROR);
// 	*path = ft_strdup(*path_env);
// 	if (!*path)
// 		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
// 	return (SUCCESS);
// }

// char	*create_full_path(char *dir, char *command)
// {
// 	char	*full_path;
// 	char	*tmp;

// 	full_path = ft_strjoin(dir, "/");
// 	if (!full_path)
// 		return (NULL);
// 	tmp = ft_strjoin(full_path, command);
// 	free(full_path);
// 	if (!tmp)
// 		return (NULL);
// 	return (tmp);
// }

// int	check_single_path(char *dir, char *command, char *path)
// {
// 	char	*full_path;

// 	full_path = create_full_path(dir, command);
// 	if (!full_path)
// 	{
// 		free(dir);
// 		free(path);
// 		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
// 	}
// 	if (access(full_path, F_OK | X_OK) == 0)
// 	{
// 		free(full_path);
// 		free(dir);
// 		free(path);
// 		return (TRUE);
// 	}
// 	free(full_path);
// 	return (FALSE);
// }

// int	check_command_in_path(char *command)
// {
// 	char	*path_env;
// 	char	*path;
// 	char	*dir;
// 	char	*path_ptr;
// 	int		result;

// 	if (init_path_check(&path_env, &path))
// 		return (FALSE);
// 	path_ptr = path;
// 	while ((dir = get_next_path(&path_ptr)))
// 	{
// 		result = check_single_path(dir, command, path);
// 		if (!result)
// 			return (result);
// 		free(dir);
// 	}
// 	free(path);
// 	return (TRUE);
// }
