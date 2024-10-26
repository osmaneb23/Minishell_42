/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:53:33 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/27 00:58:06 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_type_to_tokens(void)
{
	t_token	*token;
	t_data	*data;

	data = get_data();
	token = data->token;
	while (token)
	{
		token->type = determine_basic_type(token->value);
		if (!token->prev && token->type == ARG)
			token->type = CMD;
		if (token->prev)
		{
			if (token->prev->type == PIPE && token->type == ARG)
				token->type = CMD;
			if (token->prev->type <= APPEND && token->type == CMD)
				token->type = ARG;
			if (token->prev->type == CMD && token->type == CMD)
				token->type = ARG;
			if (token->prev->type == ARG && token->type == CMD)
				token->type = ARG;
		}
		token = token->next;
	}
}

int	determine_basic_type(char *value)
{
	if ((value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		|| (value[0] == '\'' && value[ft_strlen(value) - 1] == '\''))
		return (ARG);
	if (ft_strcmp(value, "<") == 0)
		return (INPUT);
	if (ft_strcmp(value, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(value, ">") == 0)
		return (TRUNC);
	if (ft_strcmp(value, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(value, "|") == 0)
		return (PIPE);
	return (CMD);
}
