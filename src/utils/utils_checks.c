/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:15:55 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 02:30:33 by obouayed         ###   ########.fr       */
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

bool	check_filecmd_access(char *cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/' || cmd[i] == '.')
		{
			if (access(cmd, F_OK | X_OK) != 0)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
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
