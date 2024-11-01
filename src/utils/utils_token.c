/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:54:43 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 01:47:05 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(t_data *data)
{
	t_token	*token;
	char	*tmp;

	token = data->token;
	while (token)
	{
		if ((token->value[0] == '"' && token->value[ft_strlen(token->value)
					- 1] == '"') || (token->value[0] == '\''
				&& token->value[ft_strlen(token->value) - 1] == '\''))
		{
			tmp = ft_substr(token->value, 1, ft_strlen(token->value) - 2);
			if (!tmp)
				cleanup(ERROR, "Error: malloc failed\n", ERROR, 2);
			free(token->value);
			token->value = tmp;
		}
		token = token->next;
	}
}

void	printf_tokens(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		printf("Token [value: %s | type: %d (", token->value, token->type);
		if (token->type == 1)
			printf("INPUT)]\n");
		else if (token->type == 2)
			printf("HEREDOC)]\n");
		else if (token->type == 3)
			printf("TRUNC)]\n");
		else if (token->type == 4)
			printf("APPEND)]\n");
		else if (token->type == 5)
			printf("PIPE)]\n");
		else if (token->type == 6)
			printf("CMD)]\n");
		else if (token->type == 7)
			printf("ARG)]\n");
		token = token->next;
	}
}

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}
