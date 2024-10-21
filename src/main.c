/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/21 21:23:29 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	}
	return (0);
}