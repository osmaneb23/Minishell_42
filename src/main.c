/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/01 01:45:30 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_pid;

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
			remove_quotes(data);
			printf_tokens(data);
			check_misplacements(data);
			if (check_valid_commands(data))
				cleanup(127, NULL, NO_EXIT, 2);
			else
				free_tokens(&data);
		}
		add_history(data->line);
	}
	rl_clear_history();
	return (cleanup(SUCCESS, NULL, NO_EXIT, 1));
}
