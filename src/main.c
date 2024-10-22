/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/22 03:57:51 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void tokenization(char *line)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*token;
	t_token			*head;

	i = 0;
	j = 0;
	k = 0;
	head = NULL;
	
	if (!line)
		return ;
	head = malloc(sizeof(t_token));
	
}

bool	openquote(char *line)
{
	unsigned int	i;
	unsigned int	squote;
	unsigned int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (line[i])
	{
		if (line[i] == 34)
			dquote++;
		if (line[i] == 39)
			squote++;
		i++;
	}
	if (squote % 2 != 0 || dquote % 2 != 0)
		return (1);
	return (0);
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
		tokenization(line);
	}
	return (0);
}