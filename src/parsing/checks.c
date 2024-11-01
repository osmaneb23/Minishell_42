/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:43:51 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 03:58:27 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_openquote(char *line)
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
		return (cleanup(2, "Error: open quote\n", NO_EXIT, 2));
	return (SUCCESS);
}

int	check_misplacements(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (check_misplacements_pipe(token))
			return (cleanup(2, NULL, NO_EXIT, 0));
		if (check_misplacements_redirection(token))
			return (cleanup(2, NULL, NO_EXIT, 0));
		token = token->next;
	}
	return (SUCCESS);
}

int	check_valid_commands(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (token->type == CMD && !is_builtin(token->value))
		{
			if (contains_char(token->value, '/'))
			{
				if (access(token->value, F_OK | X_OK) != 0)
					return (printf("%s: No such file or directory\n",
							token->value), cleanup(127, NULL, NO_EXIT, 0));
			}
			else
			{
				if (check_command_in_path(token->value))
					return (printf("%s: command not found\n", token->value),
						cleanup(127, NULL, NO_EXIT, 0));
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}
