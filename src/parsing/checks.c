/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:43:51 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/27 02:08:14 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_commands(t_data *data)
{
	t_token	*token;
	int		is_builtin;

	
	token = data->token;
	while (token)
	{
		if (token->type == CMD)
		{
			is_builtin = (ft_strcmp(token->value, "echo") == 0 || ft_strcmp(token->value, "cd") == 0
		|| ft_strcmp(token->value, "pwd") == 0 || ft_strcmp(token->value, "export") == 0
		|| ft_strcmp(token->value, "unset") == 0 || ft_strcmp(token->value, "env") == 0
		|| ft_strcmp(token->value, "exit") == 0);
			if (!is_builtin)
				return (printf("%s: command not found\n", token->value), ERROR);
		}
		token = token->next;
	}
	return (SUCCESS);
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
	else
	{
		if (!token->next)
		{
			if (token->type <= APPEND)
				return (cleanup(2,
						"syntax error near unexpected token `newline'\n",
						NO_EXIT, 2));
		}
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
