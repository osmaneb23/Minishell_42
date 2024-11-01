/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:43:51 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 01:44:46 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_commands(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (token->type == CMD)
		{
			if (!is_builtin(token->value))
			{
				if (!check_filecmd_access(token->value))
					return (printf("%s: No such file or directory\n",
							token->value), cleanup(127, NULL, NO_EXIT, 1));
				if (!check_command_in_path(token->value))
					return (printf("%s: command not found\n", token->value),
						cleanup(127, NULL, NO_EXIT, 1));
			}
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
