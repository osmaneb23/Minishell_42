/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/03 18:47:04 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_pid;


void sigint_handler(int sig)
{
    (void)sig;
    // If there's a child process running
    if (g_pid != 0)
    {
        kill(g_pid, SIGINT);
        write(STDERR_FILENO, "\n", 1);
        g_pid = 0;
    }
    else
    {
        // Clear the current line and print a new prompt
        write(STDERR_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void sigquit_handler(int sig)
{
    (void)sig;
    // If there's a child process running
    if (g_pid != 0)
    {
        kill(g_pid, SIGQUIT);
        printf("Quit (core dumped)\n");
        g_pid = 0;
    }
    // Do nothing if no child process
}

void setup_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    // Setup SIGINT handler (ctrl-C)
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    // Setup SIGQUIT handler (ctrl-\)
    sa_quit.sa_handler = sigquit_handler;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	initialize_data(&data, env);
	g_pid = 0;
	setup_signals();
    make_env(data, env);
	while (1)
	{
		data->line = readline("minishell$ ");
		if (!check_openquote(data->line))
		{
			tokenization(data->line);
			remove_quotes(data);
			printf_tokens(data);
			if (!check_misplacements(data))
			{
				if (!check_valid_commands(data))
                {
                    init_cmd(data);
                    exec(data);
                    free_commands(&data);
                    free_tokens(&data);
                }
			}
		}
		add_history(data->line);
	}
	rl_clear_history();
	return (cleanup(SUCCESS, NULL, NO_EXIT, 0));
}
