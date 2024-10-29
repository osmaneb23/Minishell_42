/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:15:55 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/29 20:33:30 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
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

int	check_misplacements_pipe(t_token *token)
{
	if (!token->prev)
	{
		if (token->type == PIPE)
			return (cleanup(2, "syntax error near unexpected token `|'\n",
					NO_EXIT, 2));
	}
	else
	{
		if ((token->type == PIPE && token->prev->type == PIPE)
			|| (token->type == PIPE && token->prev->type <= APPEND))
			return (cleanup(2, "syntax error near unexpected token `|'\n",
					NO_EXIT, 2));
	}
	if (!token->next)
	{
		if (token->type == PIPE)
			return (cleanup(2, "syntax error near unexpected token `|'\n",
					NO_EXIT, 2));
	}
	return (SUCCESS);
}

int	check_misplacements_redirection(t_token *token)
{
	if (token->prev)
	{
		if (token->type <= APPEND && token->prev->type <= APPEND)
		{
			printf("syntax error near unexpected token `%s'\n", token->value);
			return (cleanup(2, NULL, NO_EXIT, 2));
		}
		if (token->type <= APPEND && token->prev->type == PIPE)
			return (cleanup(2, "syntax error near unexpected token `newline'\n",
					NO_EXIT, 2));
	}
	if (!token->next)
	{
		if (token->type <= APPEND)
			return (cleanup(2, "syntax error near unexpected token `newline'\n",
					NO_EXIT, 2));
	}
	return (SUCCESS);
}
