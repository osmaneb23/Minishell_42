/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:15:55 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/03 17:57:06 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Check if a pipe is misplaced
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

// Check if there is a misplacement of redirections
int	check_misplacements_redirection(t_token *token)
{
	if (token->prev)
	{
		if (token->type <= APPEND && token->prev->type <= APPEND)
		{
			printf("syntax error near unexpected token `%s'\n", token->value);
			return (cleanup(2, NULL, NO_EXIT, 2));
		}
		if (token->type <= APPEND && token->prev->type == PIPE && !token->next)
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

// Check if the command is a builtin (echo, cd, pwd, export, unset, env, exit)
bool	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	check_access(t_token *token)
{
	struct stat	path_stat;

	if (access(token->value, F_OK) != 0)
		return (printf("%s: No such file or directory\n", token->value), 127);
	if (stat(token->value, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (printf("%s: Is a directory\n", token->value), 126);
	if (access(token->value, X_OK) != 0)
		return (printf("%s: Permission denied\n", token->value), 126);
	return (SUCCESS);
}
