/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/02 22:18:58 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	initialize_data(&data, env);
	setup_signals();
	while (1)
	{
		data->line = readline("minishell$ ");
		if (data->line == NULL)
		{
			rl_clear_history();
			return (cleanup(SUCCESS, "exit\n", NO_EXIT, 2));
		}
		check_everything(data);
		add_history(data->line);
	}
	rl_clear_history();
	return (cleanup(SUCCESS, NULL, NO_EXIT, 0));
}
