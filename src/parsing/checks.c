/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:43:51 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/29 18:58:03 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Check if command is a builtin
static int is_builtin_command(const char *cmd)
{
    return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 
        || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
        || ft_strcmp(cmd, "exit") == 0);
}

// Check if command contains path characters
static int check_command_path_access(char *cmd)
{
    unsigned int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '/' || cmd[i] == '.')
        {
            if (access(cmd, F_OK | X_OK) != 0)
            {
                printf("%s: No such file or directory\n", cmd);
                return (cleanup(127, NULL, NO_EXIT, 1));
            }
        }
        i++;
    }
    return (SUCCESS);
}

// Main function to validate commands
int check_valid_commands(t_data *data)
{
    t_token *token;

    token = data->token;
    while (token)
    {
        if (token->type == CMD)
        {
            if (!is_builtin_command(token->value))
            {
                if (!check_command_in_path(token->value))
                    return (printf("%s: command not found\n", token->value),
                        cleanup(127, NULL, NO_EXIT, 1));
                if (check_command_path_access(token->value) != SUCCESS)
                    return (ERROR);
            }
        }
        token = token->next;
    }
    return (SUCCESS);
}

// Initialize path checking variables
static int init_path_check(char **path_env, char **path)
{
    *path_env = getenv("PATH");
    if (!*path_env)
        return (false);
    *path = ft_strdup(*path_env);
    if (!*path)
        return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
    return (SUCCESS);
}

// Create full path for command
static char *create_full_path(char *dir, char *command)
{
    char *full_path;
    char *tmp;

    full_path = ft_strjoin(dir, "/");
    if (!full_path)
        return (NULL);
    tmp = ft_strjoin(full_path, command);
    free(full_path);
    if (!tmp)
        return (NULL);
    return (tmp);
}

// Check command in single path
static int check_single_path(char *dir, char *command, char *path)
{
    char *full_path;

    full_path = create_full_path(dir, command);
    if (!full_path)
    {
        free(dir);
        free(path);
        return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
    }
    if (access(full_path, F_OK | X_OK) == 0)
    {
        free(full_path);
        free(dir);
        free(path);
        return (true);
    }
    free(full_path);
    return (false);
}

// Main function to check command in PATH
int check_command_in_path(char *command)
{
    char *path_env;
    char *path;
    char *dir;
    char *path_ptr;
    int result;

    if (init_path_check(&path_env, &path) != SUCCESS)
        return (false);
    path_ptr = path;
    while ((dir = get_next_path(&path_ptr)))
    {
        result = check_single_path(dir, command, path);
        if (result != false)
            return (result);
        free(dir);
    }
    free(path);
    return (false);
}

int	check_command_in_path(char *command)
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	*full_path;
	char	*path_ptr;
	char	*tmp;

	path_env = getenv("PATH");
	if (!path_env)
		return (false);
	path = ft_strdup(path_env);
	if (!path)
		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
	path_ptr = path;
	while ((dir = get_next_path(&path_ptr)))
	{
		full_path = ft_strjoin(dir, "/");
		if (!full_path)
		{
			free(dir);
			free(path);
			return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
		}
		tmp = ft_strjoin(full_path, command);
		free(full_path);
		free(dir);
		if (!tmp)
		{
			free(path);
			return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
		}
		full_path = tmp;
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free(full_path);
			return(true);
		}
		free(full_path);
	}
	free(path);
	return (false);
}

int	check_misplacements(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (check_misplacements_pipe(token))
			return (2);
		if (check_misplacements_redirection(token))
			return (2);
		token = token->next;
	}
	return (SUCCESS);
}

bool	openquote(char *line)
{
	unsigned int	i;
	bool			squote_open;
	bool			dquote_open;

	i = 0;
	squote_open = false;
	dquote_open = false;
	while (line[i])
	{
		if (line[i] == 34 && !squote_open)
			dquote_open = !dquote_open;
		if (line[i] == 39 && !dquote_open)
			squote_open = !squote_open;
		i++;
	}
	if (squote_open || dquote_open)
		return (true);
	return (false);
}
