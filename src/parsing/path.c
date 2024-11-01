/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 01:44:17 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 03:41:28 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_command_in_path(char *command)
{
	char	*path;
	char	*dir;

	path = getenv("PATH");
	if (!path)
		return (ERROR);
	dir = get_next_path(???);
	while (dir)
	{
		if (check_single_path(???))
			return (ERROR);
		dir = get_next_path(???);
	}
	free(path);
	return (SUCCESS);
}

char *get_next_path(char **path)
{
    char *dir;
    int len;
    
    len = 0;
    dir = *path;
    // Count characters until ':' or '\0'
    while ((*path)[len] && (*path)[len] != ':')
        len++;
        
    // Move path pointer forward for next call
    if ((*path)[len] == ':')
        *path += len + 1;
    else
        *path += len;  // We reached the end
        
    // You might want to malloc and copy the directory here
    // Or handle it differently depending on your needs
    
    return (dir);
}

int check_single_path(char *dir, char *command)
{
    char full_path[1024];  // Or whatever size management you use
    
    // Combine dir + '/' + command
    // You can use your string functions here
    ft_strlcpy(full_path, dir, sizeof(full_path));
    ft_strlcat(full_path, "/", sizeof(full_path));
    ft_strlcat(full_path, command, sizeof(full_path));
    
    return (access(full_path, F_OK | X_OK) != 0);
}

