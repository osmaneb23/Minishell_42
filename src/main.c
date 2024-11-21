/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/21 17:19:49 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    process_variable(t_token *token, t_data *data)
{
    char    *value;
    char    *tmp;
    char    *tmp2;

    tmp2 = token->value;
    if (token->value[0] == '"')
        token->value = ft_substr(token->value, 2,
                ft_strlen(token->value) - 3);
    else
        token->value = ft_substr(token->value, 1,
                ft_strlen(token->value) - 1);
    free(tmp2);
    if (ft_strcmp(token->value, "$?"))
        value = ft_itoa(data->exit_status);
    else
        value = search_env_var(token->value);
    if (value)
    {
        tmp = token->value;
        token->value = value;
        free(tmp);
    }
}

void    replace_value_with_variable(t_data *data)
{
    t_token    *token;

    token = data->token;
    while (token)
    {
        if ((token->value[0] == '$') || (token->value[0] == '"'
                && token->value[1] == '$'))
            process_variable(token, data);
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
		init_environment(data, envp);
		replace_value_with_variable(data);
		remove_quotes(data);
			printf("\n");
        init_cmd(data);
        exec(data);
		printf_tokens(data);
		if (!check_misplacements(data))
		{
			if (!check_valid_commands(data))
				cleanup(SUCCESS, NULL, NO_EXIT, 0);
		}
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	initialize_data(&data);
	setup_signals();
	while (1)
	{
		data->line = readline("minishell> ");
		if (data->line == NULL)
		{
			rl_clear_history();
			return (cleanup(SUCCESS, "exit\n", NO_EXIT, 2));
		}
		if (ft_strlen(data->line) == 0)
			continue ;
		main_routine(data, envp);
		add_history(data->line);
	}
	rl_clear_history();
	return (cleanup(SUCCESS, NULL, NO_EXIT, 0));
}
