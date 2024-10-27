/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/27 03:21:03 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	(void)ac;
	(void)av;
	initialize_data(&data, env);
	while (1)
	{
		data->line = readline("minishell$ ");
		if (openquote(data->line))
			cleanup(2, "Error: open quote\n", NO_EXIT, 2);
		else
		{
			tokenization(data->line);
			printf_tokens(data);
			check_misplacements(data);
			if (check_valid_commands(data))
				cleanup(127, NULL, NO_EXIT, 2);
			else
				free_tokens(&data);	
		}
	}
	return (cleanup(SUCCESS, NULL, NO_EXIT, 1));
}
