/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:42:34 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/04 19:38:22 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Tokenize the line (split the line into tokens)
bool	tokenization(char *line)
{
	unsigned int	i;
	char			*value;
	bool			squote_open;
	bool			dquote_open;

	i = 0;
	value = NULL;
	squote_open = false;
	dquote_open = false;
	if (!line)
		return (SUCCESS);
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == 34 && !squote_open)
			dquote_open = !dquote_open;
		if (line[i] == 39 && !dquote_open)
			squote_open = !squote_open;
		value = tokenizer(line, &i, &squote_open, &dquote_open);
		create_token(value);
	}
	assign_type_to_tokens();
	return (SUCCESS);
}

char	*tokenizer(char *line, unsigned int *i, bool *squote_open,
		bool *dquote_open)
{
	unsigned int	j;
	char			*value;

	if (!*squote_open && !*dquote_open)
	{
		j = *i;
		if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
		{
			(*i)++;
			if ((line[*i] == '<' && line[*i - 1] == '<') || (line[*i] == '>'
					&& line[*i - 1] == '>'))
				(*i)++;
		}
		else
		{
			while (line[*i] != ' ' && line[*i] != '<' && line[*i] != '>'
				&& line[*i] != '|' && line[*i])
				(*i)++;
		}
		value = ft_substr(line, j, *i - j);
		while (line[*i] == ' ')
			(*i)++;
		return (value);
	}
	return (handle_quote(line, i, squote_open, dquote_open));
}

char	*handle_quote(char *line, unsigned int *i, bool *squote_open,
		bool *dquote_open)
{
	unsigned int	j;
	char			*value;

	j = *i;
	while ((*squote_open || *dquote_open) && line[*i])
	{
		(*i)++;
		if (line[*i] == 34 && !*squote_open)
			*dquote_open = !*dquote_open;
		if (line[*i] == 39 && !*dquote_open)
			*squote_open = !*squote_open;
	}
	while (line[*i] != ' ' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '|' && line[*i])
		(*i)++;
	value = ft_substr(line, j, *i - j);
	while (line[*i] == ' ')
		(*i)++;
	return (value);
}

bool	create_token(char *value)
{
	t_token	*token;
	t_data	*data;

	data = get_data();
	if (!value)
		return (cleanup(ERROR, "Error: impossible to create token\n", ERROR,
				2));
	token = malloc(sizeof(t_token));
	if (!token)
		return (cleanup(ERROR, "Error: malloc failed\n", ERROR, 2));
	token->value = value;
	token->type = 0;
	token->next = NULL;
	token->prev = NULL;
	if (!data->token)
		data->token = token;
	else
		add_token_to_list(token, data->token);
	return (SUCCESS);
}

bool	add_token_to_list(t_token *token, t_token *data_token)
{
	t_token	*last;

	if (!token || !data_token)
		return (cleanup(ERROR, "Error: impossible to add token to list\n",
				ERROR, 2));
	last = last_token(data_token);
	if (!last)
		return (cleanup(ERROR, "Error: impossible to get last token\n", ERROR,
				2));
	last->next = token;
	token->prev = last;
	return (SUCCESS);
}
