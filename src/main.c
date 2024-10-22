/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/22 21:11:49 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		printf("Error: malloc failed\n");
		return (NULL);
	}
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

// void	tokenization(char *line)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	unsigned int	k;
// 	char			*value;
// 	t_token			*head;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	head = NULL;
// 	head = malloc(sizeof(t_token));
// 	if (!line)
// 		return ;
// 	while (line[i])
// 	{
// 		if (line[i] == 34 || line[i] == 39)
// 		{
// 			value = malloc(sizeof(char) * 2);
// 			value[0] = line[i];
// 			value[1] = '\0';
// 			i++;
// 			while (line[i] && line[i] != 34 && line[i] != 39)
// 			{
// 				value = realloc(value, sizeof(char) * (j + 2));
// 				value[j] = line[i];
// 				value[j + 1] = '\0';
// 				i++;
// 				j++;
// 			}
// 			value = realloc(value, sizeof(char) * (j + 2));
// 			value[j] = line[i];
// 			value[j + 1] = '\0';
// 			j = 0;
// 			i++;
// 		}
// 		else if (line[i] == 32)
// 		{
// 			value = malloc(sizeof(char) * 2);
// 			value[0] = line[i];
// 			value[1] = '\0';
// 			i++;
// 		}
// 		else
// 		{
// 			value = malloc(sizeof(char) * 2);
// 			value[0] = line[i];
// 			value[1] = '\0';
// 			i++;
// 			while (line[i] && line[i] != 32 && line[i] != 34 && line[i] != 39)
// 			{
// 				value = realloc(value, sizeof(char) * (j + 2));
// 				value[j] = line[i];
// 				value[j + 1] = '\0';
// 				i++;
// 				j++;
// 			}
// 			j = 0;
// 		}
// 		i++;
// 	}
// }

#include <stdbool.h>

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
	struct sigaction sa;
	char *line;
	while (1)
	{
		line = readline("minishell$ ");
		if (openquote(line))
			printf("Error: unclosed quote\n");
		// tokenization(line);
	}
	return (0);
}