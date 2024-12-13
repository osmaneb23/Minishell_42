/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/11 18:30:37 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//! laisser ici ?
bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

//! laisser ici ?
//?OKOK
void init_env(t_data *data, char **env)
{
    int i;
    
    i = 0;
    data->envp = NULL;
    if (!(*env))
    {
        init_env_if_le_correcteur_clc(data);
        return ;
    }
    while (env[i])
    {
        append_node_envp(&data->envp, env[i]);
        i++;
    }
}

void	replace_var_val(t_data *data)
{
	t_token	*token;
	size_t	len;
	char	*new_value;

	token = data->token;
	while (token)
	{
		len = estimate_new_length(token->value, data);
		new_value = malloc(sizeof(char) * len);
		if (!new_value)
			cleanup(ERROR, ERR_MALLOC, ERROR, 2);
		main_handle_var(token->value, new_value, data);
		free(token->value);
		token->value = new_value;
		token = token->next;
	}
}

bool	main_routine(t_data *data, char **envp)
{
	(void)envp;
	if (!check_openquote(data->line))
	{
		tokenization(data->line);
		if (ft_strlen(data->token->value) == 0)
			return (cleanup(SUCCESS, NULL, NO_EXIT, 0));
		replace_var_val(data); // \$
		remove_quotes(data);
		printf_tokens(data);
		printf("\n");
		if (!check_misplacements(data))
		{
			if (!check_valid_commands(data))
			{
				if (!init_cmd(data))
				{
					if (!exec(data))
						cleanup(SUCCESS, NULL, NO_EXIT, 0);
				}
			}
		}
		
	}
	return (SUCCESS);
}

#define WHITE "\033[0;37m"
#define BWHITE "\033[1;37m"
#define DEFAULT "\033[0m"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	initialize_data(&data);
	setup_signals();
	init_env(data, envp);
	printf(WHITE);
	while (1)
	{
		data->line = readline("minishell> ");
		if (data->line == NULL)
		{
			rl_clear_history();
			return (cleanup(SUCCESS, "exit\n", NO_EXIT, 1));
		}
		if (ft_strlen(data->line) == 0)
			continue ;
		main_routine(data, envp);
		add_history(data->line);
		free(data->line); // ??
	}
	rl_clear_history();
	printf(DEFAULT);
	return (cleanup(SUCCESS, NULL, SUCCESS, 0));
}

//? LEAKS

//! cas env BIZARRE