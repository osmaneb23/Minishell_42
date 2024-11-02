/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:11:36 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/02 22:20:05 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	if (sigemptyset(&sa_int.sa_mask) == -1)
		cleanup(ERROR, "Error: sigemptyset failed\n", ERROR, 2);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		cleanup(ERROR, "Error: sigaction failed\n", ERROR, 2);
	sa_quit.sa_handler = sigquit_handler;
	if (sigemptyset(&sa_quit.sa_mask) == -1)
		cleanup(ERROR, "Error: sigemptyset failed\n", ERROR, 2);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		cleanup(ERROR, "Error: sigaction failed\n", ERROR, 2);
}

void	sigint_handler(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	if (data && data->current_pid != 0)
	{
		if (kill(data->current_pid, SIGINT) == -1)
			cleanup(ERROR, "Error: kill failed\n", ERROR, 2);
		ft_putstr_fd("\n", 2);
		data->current_pid = 0;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	data->exit_status = 130;
}

void	sigquit_handler(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	if (data && data->current_pid != 0)
	{
		if (kill(data->current_pid, SIGQUIT) == -1)
			cleanup(ERROR, "Error: kill failed\n", ERROR, 2);
		ft_putstr_fd("Quit (core dumped)\n", 2);
		data->current_pid = 0;
		data->exit_status = 131;
	}
}
