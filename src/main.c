/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/26 04:06:43 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*get_data(void)
{
	static t_data	data;

	return (&data);
}

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

bool	add_token_to_list(t_token *token, t_token *data_token)
{
	t_token	*last;

	if (!token || !data_token)
		return (cleanup(NULL, true, "Error: impossible to add token to list\n"));
	last = last_token(data_token);
	if (!last)
		return (cleanup(NULL, true, "Error: impossible to get last token\n"));
	last->next = token;
	token->prev = last;
	return (SUCCESS);
}

int	determine_type(char *value)
{
	if (!value)
		return (cleanup(NULL, true, "Error: impossible to determine type\n"), FAILURE);
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

bool	create_token(char *value, int type)
{
	t_token	*token;
	t_data	*data;

	data = get_data();
	if (!value || !type)
		return (cleanup(NULL, true, "Error: impossible to create token\n"),
			NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (cleanup(NULL, true, "Error: malloc failed\n"), NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	if (!data->token)
		data->token = token;
	else
		add_token_to_list(token, data->token);
	return (SUCCESS);
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
	(*i)++;
	value = ft_substr(line, j, *i - j);
	while (line[*i] == ' ')
		(*i)++;
	return (value);
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
		return ;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == 34 && !squote_open)
			dquote_open = !dquote_open;
		if (line[i] == 39 && !dquote_open)
			squote_open = !squote_open;
		value = tokenizer(line, &i, &squote_open, &dquote_open);
		if (create_token(value, determine_type(value)))
			return (cleanup(NULL, true, "Error: tokenization failed\n"));
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

void	initialize_data(t_data **data, char **env)
{
	*data = get_data();
	(*data)->token = NULL;
	(*data)->username = ft_strdup(env[0]);
}

int	main(int ac, char **av, char **env)
{
	char *line;
	t_data *data;

	initialize_data(&data, env);
	while (1)
	{
		line = readline("minishell$ ");
		if (openquote(line))
			printf("Error: unclosed quote\n");
		else
		{
			if (tokenization(line))
				return (ERROR);
		}
	}
	return (SUCCESS);
}