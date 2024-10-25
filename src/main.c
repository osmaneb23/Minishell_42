/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/25 02:07:10 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	determine_type(char *value)
{
	if (!value)
		return (cleanup(NULL, true, "Error: impossible to determine type\n"));
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

t_token	*create_token(char *value, int type)
{
	t_token	*token;

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
	printf("token->value: %s\n", token->value);
	printf("token->type: %d\n", token->type);
	return (token);
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
		while (line[*i] == ' ')
			(*i)++;
		return (ft_substr(line, j, *i - j));
	}
	return (handle_quote(line, i, squote_open, dquote_open));
}

void	tokenization(char *line)
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
		create_token(value, determine_type(value));
	}
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

int	main(int ac, char **av)
{
	char *line;
	while (1)
	{
		line = readline("minishell$ ");
		if (openquote(line))
			printf("Error: unclosed quote\n");
		else
		{
			tokenization(line);
		}
	}
	return (0);
}