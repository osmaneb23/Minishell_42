/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:43:51 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/29 21:10:53 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_commands(t_data *data)
{
	t_token			*token;
	int				is_builtin;
	unsigned int	i;

	i = 0;
	token = data->token;
	while (token)
	{
		if (token->type == CMD)
		{
			is_builtin = (ft_strcmp(token->value, "echo") == 0
				|| ft_strcmp(token->value, "cd") == 0 || ft_strcmp(token->value,
					"pwd") == 0 || ft_strcmp(token->value, "export") == 0
				|| ft_strcmp(token->value, "unset") == 0
				|| ft_strcmp(token->value, "env") == 0
				|| ft_strcmp(token->value, "exit") == 0);
			if (!is_builtin)
			{
				if (!check_command_in_path(token->value))
					return (printf("%s: command not found\n", token->value),
						cleanup(127, NULL, NO_EXIT, 1));
				while (token->value[i])
				{
					if (token->value[i] == '/' || token->value[i] == '.')
					{
						if (access(token->value, F_OK | X_OK) != 0)
						{
							printf("%s: No such file or directory\n",
								token->value);
							return (cleanup(127, NULL, NO_EXIT, 1));
						}
					}
					i++;
				}
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

bool	check_single_path(char *dir, char *command, char *path)
{
	char	*full_path;
	char	*tmp;

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
		return (true);
	}
	free(full_path);
    return (false);
}

int	check_command_in_path(char *command)
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	*path_ptr;

	path_env = getenv("PATH");
	if (!path_env)
		return (false);
	path = ft_strdup(path_env);
	if (!path)
		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
	path_ptr = path;
	while ((dir = get_next_path(&path_ptr)))
	{
        if (check_single_path(dir, command, path))
            return (true);
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
